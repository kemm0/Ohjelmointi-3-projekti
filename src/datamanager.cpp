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
    return;

    QJsonArray jsonArray = toJSONPref();
    QUrl fullFilePath = QUrl(path + "/" + filename + ".data").toLocalFile();

    QFile file(fullFilePath.toString());

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument saveDocument(jsonArray);

    qDebug()<<"Saving";

    file.write(saveDocument.toJson());
}

void DataManager::loadPrefFromFile(QString filepath)
{
    //Tää pitäis muokata niin, että tehdään apikutsu
    qDebug()<<"Loading preferences...";
    return;

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

QJsonArray DataManager::toJSONPref()
{
    QJsonArray jsonArray;

    for (auto value : data_){
        QJsonObject jsonObject;
        jsonObject.insert("location",value.second->getLocation());
        jsonObject.insert("datatype", value.second->getDatatype());
        jsonArray.push_back(jsonObject);
    }

    return jsonArray;

}

void DataManager::removeData(QString &id)
{
    data_.erase(id);
}


