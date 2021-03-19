#include "api_caller.h"

API_caller::API_caller(QObject *parent) : QObject(parent)
{

}

void API_caller::fetchData(DataRequest dataRequest)
{
    //if (APIs_.find(dataRequest.datatype) == APIs_.end()) {
    //    qDebug() << "Invalid datatype.";
    //    return nullptr;
    //} else {
    //    return APIs_.find(dataRequest.datatype)->second->fetchData(dataRequest);
    //}
    auto api_it = std::make_shared<API_Ilmatieteenlaitos>();
    api_it->fetchData(dataRequest);
}

std::map<QString, std::shared_ptr<API> > API_caller::getAPIs()
{
    return APIs_;
}
