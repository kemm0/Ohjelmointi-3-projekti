#include "apicallmanager.h"
#include "apicaller.hh"
#include "apicallerfmi.hh"
#include "apicallerfingrid.hh"

APICallManager::APICallManager(QObject *parent) : QObject(parent)
{
}

void APICallManager::fetchData(DataRequest dataRequest)
{
    if(APICallerFMI::dataTypes().contains(dataRequest.datatype)){
        auto api = new APICallerFMI(this);
        api->fetchData(dataRequest);
        connect(api,&APICallerFMI::dataParsed,this,&APICallManager::forwardData);
        connect(api,&APICallerFMI::requestError,this,&APICallManager::forwardErrorMessage);
    }
    else if(APICallerFingrid::dataTypes().contains(dataRequest.datatype)){
        auto api = new APICallerFingrid(this);
        api->fetchData(dataRequest);
        connect(api,&APICallerFingrid::dataParsed,this,&APICallManager::forwardData);
        connect(api,&APICallerFingrid::requestError,this,&APICallManager::forwardErrorMessage);
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
