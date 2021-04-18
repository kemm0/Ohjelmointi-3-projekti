#include "backend.h"

Backend::Backend(QString apiConfigPath, QObject *parent) :
    QObject(parent),
    apiConfig_({})
{
    loadAPIConfig(apiConfigPath);
    apiCallManager_ = std::make_shared<APICallManager>();
    dataManager_ = std::make_shared<DataManager>();
    connect(apiCallManager_.get(), &APICallManager::dataFetched, dataManager_.get(), &DataManager::addData);
    connect(apiCallManager_.get(), &APICallManager::requestError, this, &Backend::sendError);
    connect(dataManager_.get(), &DataManager::dataAdded, this, &Backend::forwardData);
    connect(dataManager_.get(),&DataManager::prefLoaded, this, &Backend::requestPrefData);
    apiCallManager_->Register("FMI","",&APICallerFMI::Create);
    apiCallManager_->Register("Fingrid",apiConfig_["FINGRID_API_KEY"],&APICallerFingrid::Create);
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
    request.dataSource = propertyMap["dataSource"].toString();
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
    QString filePathString = filePath.toString();
    dataManager_->loadPrefFromFile(filePathString);
}

void Backend::savePreferences(QVariant filename, QVariant filepath)
{
    QString filenameString = filename.toString();
    QString pathString = filepath.toString();
    dataManager_->savePrefToFile(filenameString,pathString);
}

void Backend::requestPrefData(QJsonObject pref)
{
    qDebug()<< pref;

    QJsonArray preferences = pref["preferences"].toArray();

    for(int i = 0; i < preferences.size(); i++){
        QJsonObject prefObject = preferences[i].toObject();
        DataRequest request;
        request.datatype = prefObject["datatype"].toString();
        request.dataSource = prefObject["dataSource"].toString();
        request.location = prefObject["location"].toString();
        request.startTime = QDateTime::fromString(
                    prefObject["startTime"].toString(),Data::jsonDateTimeFormat);

        request.endTime = QDateTime::currentDateTime();
        qDebug()<<request;

        apiCallManager_->fetchData(request);
    }
}

void Backend::forwardData(std::shared_ptr<Data> data)
{
    QVariantMap dataMap = {};
    QVariantList dates = {};
    QVariantList values = {};
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
    dataMap.insert("dataSource", data->getDataSource());
    qDebug()<<"Data forwarded by backend to view";
    emit dataAdded(QVariant::fromValue(dataMap));
}

void Backend::sendError(QString errorMessage)
{
    emit error(QVariant::fromValue(errorMessage));
}

void Backend::removeData(QVariant id)
{
    QString idString = id.toString();
    dataManager_->removeData(idString);
}

void Backend::loadAPIConfig(QString path)
{
    QFile apiConfigFile(path);

    if (!apiConfigFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open apiconfig.txt file. Make sure it's in the "
        "project root folder");

        emit error("Couldn't open apiconfig.txt file. Make sure "
        "it's in the project root folder");
        return;
    }

    QTextStream in(&apiConfigFile);

    while(!in.atEnd()){
        QString line = in.readLine();
        auto parts = line.split("=");
        QString key = parts[0];
        QString value = parts[1];
        apiConfig_[key] = value;
    }
}
