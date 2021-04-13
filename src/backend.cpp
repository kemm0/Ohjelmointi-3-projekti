#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    apiCallManager_ = std::make_shared<APICallManager>();
    dataManager_ = std::make_shared<DataManager>();
    connect(apiCallManager_.get(),&APICallManager::dataFetched,dataManager_.get(),&DataManager::addData);
    connect(dataManager_.get(),&DataManager::dataAdded,this,&Backend::forwardData);
}

std::map<QString, std::vector<std::shared_ptr<Data> > > Backend::getExistingData(QString id)
{
    return {};
}

void Backend::fetchNewData(DataRequest request)
{
    qDebug()<<"Fetched: " + request;
    apiCallManager_->fetchData(request);
}

void Backend::saveData(QString filename, QString path, QString id)
{
    dataManager_->saveDataToFile(filename,path,id);
}

std::vector<std::shared_ptr<Data> > Backend::loadData(QString filepath)
{
    return {};
}

std::vector<std::shared_ptr<Data> > Backend::loadPreferences(QString filepath)
{
    return {};
}

void Backend::forwardData(std::shared_ptr<Data> data)
{
    emit dataAdded(data);
}

void Backend::removeData(QString& id)
{
    dataManager_->removeData(id);
}
