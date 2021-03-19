#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    apiCaller_ = std::make_shared<API_caller>();
    for (std::pair<QString, std::shared_ptr<API>> api : apiCaller_->getAPIs()) {
        connect(api.second.get(), &API::dataParsed, this, &Backend::requestComplete);
    }
}

std::map<QString, std::vector<std::shared_ptr<Data> > > Backend::getExistingData(QString id)
{
    return {};
}

void Backend::fetchNewData(DataRequest request)
{
    apiCaller_->fetchData(request);
}

std::vector<std::shared_ptr<Data> > Backend::loadData(QString filepath)
{
    return {};
}

std::vector<std::shared_ptr<Data> > Backend::loadPreferences(QString filepath)
{
    return {};
}

void Backend::requestComplete(std::shared_ptr<Data>)
{
    qDebug()<<"request complete";
}
