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

void DataManager::addData(std::shared_ptr<Data> data)
{
    data_.insert(std::pair<QString,std::shared_ptr<Data>>(data->getId(),data));
    qDebug()<<"Data added to datamanager";
    emit dataAdded(data);
}

void DataManager::saveDataToFile(QString filename, QString path, QString id)
{
    auto data = data_.at(id);
    QJsonObject jsonObject = data->toJSON();
    QUrl fullFilePath = QUrl(path + "/" + filename + ".data").toLocalFile();

    QFile file(fullFilePath.toString());

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument saveDocument(jsonObject);

    qDebug()<<"Saving";

    file.write(saveDocument.toJson());
}

void DataManager::loadDataFromFile(QString filepath)
{
    QUrl fullFilePath = QUrl(filepath).toLocalFile();
    QFile file(fullFilePath.toString());

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray loadData = file.readAll();

    QJsonObject jsonObject = QJsonDocument::fromJson(loadData).object();

    std::shared_ptr<Data> newData(Data::fromJSON(jsonObject));

    data_.insert(std::pair<QString,std::shared_ptr<Data>>(newData->getId(),newData));

    emit dataAdded(newData);
}

void DataManager::savePrefToFile(QString filename, QString path)
{
    //tää pitäis muokkailla erilaiseks sillee et tallentaa asetukset datan sijasta

    qDebug()<<"Saving preferences...";

    QJsonDocument saveDocument = toJSONPref();
    QUrl fullFilePath = QUrl(path + "/" + filename + ".pref").toLocalFile();

    QFile file(fullFilePath.toString());

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't save to this file. Check that the path is valid.");
        return;
    }

    file.write(saveDocument.toJson());
}

void DataManager::loadPrefFromFile(QString filepath)
{
    //Tää pitäis muokata niin, että tehdään apikutsu
    qDebug()<<"Loading preferences...";

    QUrl fullFilePath = QUrl(filepath).toLocalFile();
    QFile file(fullFilePath.toString());

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray loadData = file.readAll();

    QJsonObject jsonObject = QJsonDocument::fromJson(loadData).object();

    emit prefLoaded(jsonObject);
}

QJsonDocument DataManager::toJSONPref()
{
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonArray jsonArray = {};
    for (auto value : data_){
        QJsonObject preference;
        QDateTime startTime = value.second->getDataValues()[0].first;
        preference.insert("location",value.second->getLocation());
        preference.insert("datatype", value.second->getDatatype());
        preference.insert("dataSource", value.second->getDataSource());
        preference.insert("startTime",QJsonValue::fromVariant(startTime));
        jsonArray.append(QJsonValue(preference));
    }
    jsonObject["preferences"] = jsonArray;
    jsonDocument = QJsonDocument(jsonObject);
    return jsonDocument;
}

void DataManager::removeData(QString &id)
{
    data_.erase(id);
}


