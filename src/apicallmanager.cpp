#include "apicallmanager.h"
#include "apicallerfmi.hh"
#include "apicallerfingrid.hh"
#include <QFile>
#include <cmath>

APICallManager::APICallManager(QObject *parent) :
    QObject(parent)
{
}

void APICallManager::Register(const QString &apiName, const QString &apiKey, APICaller::CreateAPICallerFn createFn)
{
    apiCallers[apiName] = createFn;
    apiKeys[apiName] = apiKey;
}

APICaller *APICallManager::CreateAPICaller(const QString &apiName)
{
    if( !apiCallers.contains(apiName) ){
        return nullptr;
    }
    return apiCallers[apiName](apiKeys[apiName]);
}

void APICallManager::fetchData(DataRequest dataRequest)
{
    if(apiCallers.contains(dataRequest.dataSource)){
        auto api = apiCallers[dataRequest.dataSource](apiKeys[dataRequest.dataSource]);
        connect(api,&APICaller::dataParsed,this,&APICallManager::forwardData);
        connect(api,&APICaller::requestError,this,&APICallManager::forwardErrorMessage);
        api->fetchData(dataRequest);
    }
    else{
        emit requestError("No API service registered with name " + dataRequest.dataSource);
    }
}

void APICallManager::forwardData(std::shared_ptr<Data> data)
{
    emit dataFetched(data);
}

void APICallManager::forwardErrorMessage(QString errorMessage)
{
    emit requestError(errorMessage);
}
