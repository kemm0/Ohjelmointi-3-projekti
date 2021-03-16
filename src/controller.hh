#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include <memory>
#include "datamodel.hh"
#include "data.hh"
#include "view.hh"
#include "backend.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(std::shared_ptr<Backend> backend,
                        std::shared_ptr<View> view,
                        QObject *parent = nullptr);

    Q_INVOKABLE void getNewData();
    Q_INVOKABLE void getExistingData();
    Q_INVOKABLE void loadData();
    Q_INVOKABLE void loadPreferences();

signals:

private:
    std::shared_ptr<Backend> backend_;
    std::shared_ptr<View> view_;

};

#endif // CONTROLLER_HH
