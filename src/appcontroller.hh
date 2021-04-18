#ifndef APPCONTROLLER_HH
#define APPCONTROLLER_HH

#include <QObject>
#include "backend.h"

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

    void init(Backend* backend, QObject* gui);

signals:

private:
    Backend* backend_;
    QObject* gui_;
};

#endif // APPCONTROLLER_HH
