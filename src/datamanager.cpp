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
    auto data = data_.at(0);
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

void DataManager::loadPrefFromFile(QString filepath)
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

void DataManager::removeData(QString &id)
{
    data_.erase(id);
}


