#include "controller.hh"
#include "datarequest.h"
#include <QQuickItem>

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
    qmlData.insert("location",data->getLocation());
    qmlData.insert("dates",dates);
    qmlData.insert("values",values);
    qmlData.insert("unit",data->getUnit());
    qmlData.insert("datatype",data->getDatatype());
    emit requestComplete(qmlData);
}

void Controller::removeData(QVariant id)
{
    QString dataID = id.toString();
    backend_->removeData(dataID);
}

void Controller::saveData(QVariant filename, QVariant path, QVariant id)
{
    emit saveData(filename.toString(),path.toString(),id.toString());
}

void Controller::loadData(QVariant filePath)
{
    backend_->loadData(filePath.toString());
}

void Controller::backendError(QString errorMessage)
{
    emit error(errorMessage);
}

Controller::Controller(std::shared_ptr<Backend> backend, QObject *parent)
    : QObject(parent),
      backend_{backend}
{
    QObject::connect(backend_.get(),SIGNAL(error(QString)),this,SLOT(backendError(QString)));
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
    emit getNewData(request);
}

void  Controller::getExistingData()
{
}

void Controller::loadPreferences()
{
}

void Controller::setView(QObject *view)
{
    view_ = view;

    QObject::connect(view,SIGNAL(dataAdded(QVariant)),this,SLOT(getNewData(QVariant)));

    QObject::connect(view, SIGNAL(dataRemoved(QVariant)),this, SLOT(removeData(QVariant)));

    QObject::connect(this,SIGNAL(getNewData(DataRequest)),backend_.get(),SLOT(fetchNewData(DataRequest)));

    QObject::connect(backend_.get(),SIGNAL(dataAdded(std::shared_ptr<Data>)),this,SLOT(sendDataToView(std::shared_ptr<Data>)));

    QObject::connect(this,SIGNAL(saveData(QString,QString,QString)),backend_.get(),SLOT(saveData(QString,QString,QString)));

    for(auto datapanel : view->findChildren<QObject*>("dataPanel")){
        QObject::connect(datapanel,SIGNAL(saveData(QVariant,QVariant,QVariant)),this,SLOT(saveData(QVariant,QVariant,QVariant)));
        QObject::connect(datapanel,SIGNAL(loadData(QVariant)),this,SLOT(loadData(QVariant)));
    }
}
