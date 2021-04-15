#include "controller.hh"
#include "datarequest.h"
#include <QQuickItem>

Controller::Controller(std::shared_ptr<Backend> backend, QObject *parent)
    : QObject(parent),
      backend_{backend}
{
}

void Controller::setView(QObject *view)
{
    view_ = view;

    QObject::connect(view,SIGNAL(dataAdded(QVariant)),backend_.get(),SLOT(fetchNewData(QVariant)));

    QObject::connect(view, SIGNAL(dataRemoved(QVariant)),backend_.get(), SLOT(removeData(QVariant)));

    for(auto datapanel : view->findChildren<QObject*>("dataPanel")){
        QObject::connect(datapanel,SIGNAL(saveData(QVariant,QVariant,QVariant)),backend_.get(),SLOT(saveData(QVariant,QVariant,QVariant)));
        QObject::connect(datapanel,SIGNAL(loadData(QVariant)),backend_.get(),SLOT(loadData(QVariant)));
    }
}
