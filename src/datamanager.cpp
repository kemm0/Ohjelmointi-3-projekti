#include "datamanager.hh"
#include <QDebug>

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

void DataManager::saveData(std::shared_ptr<Data> data)
{
    data_.insert(std::pair<QString,std::shared_ptr<Data>>(data->getId(),data));
    emit dataAdded(data);
}

void DataManager::removeData(QString &id)
{
    data_.erase(id);
}


