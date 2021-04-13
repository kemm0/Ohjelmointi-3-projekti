#include "datamanager.hh"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDir>

DataManager::DataManager(QObject *parent) : QObject(parent)
{

}

std::vector<std::shared_ptr<Data> > DataManager::getAllData()
{
    return {};
}

qreal DataManager::getAverage(QString id)
{
    auto result = data_.find(id);

    if (result == data_.end()){
        return 0;
    }

    return 1;
}

void DataManager::addData(std::shared_ptr<Data> data)
{
    data_.insert(std::pair<QString,std::shared_ptr<Data>>(data->getId(),data));
    emit dataAdded(data);
}

void DataManager::saveDataToFile(QString filename, QString path, QString id)
{
    auto data = data_.at(id);
    QJsonObject jsonObject;
    jsonObject.insert("datatype",data->getDatatype());
    jsonObject.insert("unit",data->getUnit());
    jsonObject.insert("location",data->getLocation());
    auto dataVector = data->getDataValues();
    QJsonArray dates;
    QJsonArray values;
    for(uint i = 0; i < dataVector.size(); i++){
        dates.append(QJsonValue::fromVariant((dataVector.at(i).first)));
        values.append(QJsonValue::fromVariant((dataVector.at(i).second)));
    }
    jsonObject.insert("dates",dates);
    jsonObject.insert("values",values);
    QUrl fullFilePath = QUrl(path + "/" + filename + ".json").toLocalFile();
    QFile file(fullFilePath.toString());

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument saveDocument(jsonObject);

    file.write(saveDocument.toJson());
}

void DataManager::removeData(QString &id)
{
    data_.erase(id);
}


