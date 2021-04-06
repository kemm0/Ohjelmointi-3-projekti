#include "controller.hh"
#include "DataRequest.h"


void Controller::sendDataToView(std::vector<std::pair<QDateTime, qreal> > data)
{

}

Controller::Controller(std::shared_ptr<Backend> backend, QObject *parent)
    : QObject(parent),
      backend_{backend}
{
}

void Controller::getNewData(QVariant properties)
{
    auto propertyMap = properties.toMap();
    DataRequest request;
    request.datatype = propertyMap["dataType"].toString();
    request.location = propertyMap["location"].toString();
    request.startTime = propertyMap["startDate"].toDateTime();
    request.endTime = propertyMap["endDate"].toDateTime();
    qDebug()<<request;
    emit getNewData(request);
}

void  Controller::getExistingData()
{
    qDebug()<<":-D";
}

void Controller::loadData()
{
}

void Controller::loadPreferences()
{
}

void Controller::setView(QObject *view)
{
    view_ = view;
    QObject::connect(view,SIGNAL(dataAdded(const QVariant)),this,SLOT(getNewData(const QVariant)));
}
