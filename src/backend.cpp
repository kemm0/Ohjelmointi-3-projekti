#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    apiCallManager_ = std::make_shared<APICallManager>();
    dataManager_ = std::make_shared<DataManager>();
    connect(apiCallManager_.get(),&APICallManager::dataFetched,dataManager_.get(),&DataManager::addData);
    connect(dataManager_.get(),&DataManager::dataAdded,this,&Backend::forwardData);
    connect(apiCallManager_.get(),&APICallManager::requestError,this,&Backend::error);
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

void Backend::loadData(QString filepath)
{
    dataManager_->loadDataFromFile(filepath);
}

void Backend::forwardError(QString &errorMessage)
{
    emit error(errorMessage);
}

void Backend::loadPreferences(QString filepath)
{

}

void Backend::savePreferences(QString filename, QString path)
{

}

void Backend::forwardData(std::shared_ptr<Data> data)
{
    emit dataAdded(data);
}

void Backend::removeData(QString& id)
{
    dataManager_->removeData(id);
}
