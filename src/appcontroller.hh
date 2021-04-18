#ifndef APPCONTROLLER_HH
#define APPCONTROLLER_HH

#include <QObject>
#include "backend.h"

/**
 * @brief The AppController class is used to connect the signals and slots
 * of the GUI and backend so that the two can work together.
 */
class AppController : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief AppController creates a new AppController object
     * @param parent
     */
    explicit AppController(QObject *parent = nullptr);

    /**
     * @brief init stores the backend and gui to the AppController and does the
     * required connections between the backend and gui. This is required so
     * the Controller can work properly.
     * @param backend a pointer to the App's backend object
     * @param gui a pointer to the App's gui object
     */
    void init(Backend* backend, QObject* gui);

signals:

private:
    Backend* backend_;
    QObject* gui_;
};

#endif // APPCONTROLLER_HH
