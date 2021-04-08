#include "controller.hh"
#include "DataRequest.h"

void Controller::sendDataToView(std::shared_ptr<Data> data)
{
    QMap<QString,QVariant> qmlData = {};
    QList<QVariant> dates = {};
    QList<QVariant> values = {};
    for(uint i = 0; i < data->getDataValues().size(); i++){
        auto date = data->getDataValues()[i].first;
        auto value = data->getDataValues()[i].second;
        dates.append(date);
        values.append(value);
    }
    qmlData.insert("id",data->getId());
    qmlData.insert("dates",dates);
    qmlData.insert("values",values);
    emit requestComplete(qmlData);
}

void Controller::test(Data *data)
{
    qDebug(":D:D");
}

Controller::Controller(std::shared_ptr<Backend> backend, QObject *parent)
    : QObject(parent),
      backend_{backend}
{
}

void Controller::getNewData(QVariant properties)
{
    QString dateFormat = "dd.MM.yyyy:hh.mm";
    auto propertyMap = properties.toMap();

    QString startTimeString = propertyMap["startDate"].toString() +
            ":" + propertyMap["startTime"].toString();

    QString endTimeString = propertyMap["endDate"].toString() +
            ":" + propertyMap["endTime"].toString();

    DataRequest request;
    request.datatype = propertyMap["dataType"].toString();
    request.location = propertyMap["location"].toString();
    request.startTime = QDateTime::fromString(startTimeString,dateFormat);
    request.endTime = QDateTime::fromString(endTimeString,dateFormat);
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
    QObject::connect(view,SIGNAL(dataAdded(QVariant)),this,SLOT(getNewData(QVariant)));
    QObject::connect(this,SIGNAL(getNewData(DataRequest)),backend_.get(),SLOT(fetchNewData(DataRequest)));
    QObject::connect(backend_.get(),SIGNAL(requestComplete(std::shared_ptr<Data>)),this,SLOT(sendDataToView(std::shared_ptr<Data>)));
}
