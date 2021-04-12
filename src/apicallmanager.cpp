#include "apicallmanager.h"

APICallManager::APICallManager(QObject *parent) : QObject(parent)
{
}

void APICallManager::fetchData(DataRequest dataRequest)
{
    //if (APIs_.find(dataRequest.datatype) == APIs_.end()) {
    //    qDebug() << "Invalid datatype.";
    //    return nullptr;
    //} else {
    //    return APIs_.find(dataRequest.datatype)->second->fetchData(dataRequest);
    //}
    if(dataRequest.datatype == "Temperature"){
        auto api = new APICallerFMI(this);
        api->fetchData(dataRequest);
        connect(api,&APICallerFMI::dataParsed,this,&APICallManager::forwardData);
    }
}

void APICallManager::forwardData(std::shared_ptr<Data> data)
{
    emit dataFetched(data);
}
