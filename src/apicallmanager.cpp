#include "apicallmanager.h"
#include "apicallerfmi.hh"
#include "apicallerfingrid.hh"
#include <QFile>
#include <cmath>

APICallManager::APICallManager(QObject *parent) :
    QObject(parent),
    apiConfig_({})
{
    loadAPIConfig();
}

void APICallManager::Register(const QString &apiName, APICaller::CreateAPICallerFn createFn)
{
    apiCallers[apiName] = createFn;
}

APICaller *APICallManager::CreateAPICaller(const QString &apiName)
{
    if( !apiCallers.contains(apiName) ){
        return nullptr;
    }
    return apiCallers[apiName]();
}

void APICallManager::fetchData(DataRequest dataRequest)
{
    if(apiCallers.contains(dataRequest.dataSource)){
        auto api = apiCallers[dataRequest.dataSource]();
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
    qDebug()<<"data Forwarded";
}

void APICallManager::forwardErrorMessage(QString errorMessage)
{
    emit requestError(errorMessage);
}

void APICallManager::loadAPIConfig()
{
    QFile apiConfigFile("../kumivene-solutions/apiconfig.txt");

    if (!apiConfigFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open apiconfig.txt file. Make sure it's in the "
        "project root folder");

        emit requestError("Couldn't open apiconfig.txt file. Make sure "
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
