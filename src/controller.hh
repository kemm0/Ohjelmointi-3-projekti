#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include <memory>
#include "datamanager.hh"
#include "data.hh"
#include "backend.h"

class Controller : public QObject
{
    Q_OBJECT

public slots:
public:
    explicit Controller(std::shared_ptr<Backend> backend,
                        QObject *parent = nullptr);

    void setView(QObject* view);

private:
    std::shared_ptr<Backend> backend_;
    QObject *view_;

};

#endif // CONTROLLER_HH
