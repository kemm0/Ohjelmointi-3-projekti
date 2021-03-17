#include "api_caller.h"

API_caller::API_caller(QObject *parent) : QObject(parent)
{

}

std::shared_ptr<Data> API_caller::fetchData(DataRequest dataRequest)
{
    if (APIs_.find(dataRequest.datatype) == APIs_.end()) {
        qDebug() << "Invalid datatype.";
        return nullptr;
    } else {
        return APIs_.find(dataRequest.datatype)->second->fetchData(dataRequest);
    }
}
