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
    if(dataRequest.datatype == "Temperature" ||
       dataRequest.datatype == "Average temperature" ||
       dataRequest.datatype == "Average maximum temperature" ||
       dataRequest.datatype == "Average minimum temperature" ||
       dataRequest.datatype == "Observed wind" ||
       dataRequest.datatype == "Observed cloudiness") {
        auto api = new APICallerFMI(this);
        api->fetchData(dataRequest);
        connect(api,&APICallerFMI::dataParsed,this,&APICallManager::forwardData);
    }
}

void APICallManager::forwardData(std::shared_ptr<Data> data)
{
    emit dataFetched(data);
}
