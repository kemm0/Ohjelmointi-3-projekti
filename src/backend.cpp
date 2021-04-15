#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    apiCallManager_ = std::make_shared<APICallManager>();
    dataManager_ = std::make_shared<DataManager>();
    connect(apiCallManager_.get(), &APICallManager::dataFetched, dataManager_.get(), &DataManager::addData);
    connect(apiCallManager_.get(), &APICallManager::requestError, this, &Backend::sendError);
    connect(dataManager_.get(), &DataManager::dataAdded, this, &Backend::forwardData);
}

void Backend::fetchNewData(QVariant properties)
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

    apiCallManager_->fetchData(request);
}

void Backend::saveData(QVariant filename, QVariant path, QVariant id)
{
    QString filenameString = filename.toString();
    QString pathString = path.toString();
    QString idString = id.toString();
    dataManager_->saveDataToFile(filenameString,pathString,idString);
}

void Backend::loadData(QVariant filePath)
{
    QString filePathString = filePath.toString();
    dataManager_->loadDataFromFile(filePathString);
}

void Backend::loadPreferences(QVariant filePath)
{

}

void Backend::savePreferences(QVariant filename, QVariant filepath)
{

}

void Backend::forwardData(std::shared_ptr<Data> data)
{
    QMap<QString,QVariant> dataMap = {};
    QList<QVariant> dates = {};
    QList<QVariant> values = {};
    for(uint i = 0; i < data->getDataValues().size(); i++){
        auto date = data->getDataValues()[i].first;
        auto value = data->getDataValues()[i].second;
        dates.append(date);
        values.append(value);
    }
    dataMap.insert("id",data->getId());
    dataMap.insert("location",data->getLocation());
    dataMap.insert("dates",dates);
    dataMap.insert("values",values);
    dataMap.insert("unit",data->getUnit());
    dataMap.insert("datatype",data->getDatatype());

    emit dataAdded(dataMap);
}

void Backend::sendError(QString errorMessage)
{
    emit error(errorMessage);
}

void Backend::removeData(QVariant id)
{
    QString idString = id.toString();
    dataManager_->removeData(idString);
}
