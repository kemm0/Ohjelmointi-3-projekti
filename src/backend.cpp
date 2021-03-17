#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    apiCaller_ = std::make_shared<API_caller>();
}

std::map<QString, std::vector<std::shared_ptr<Data> > > Backend::getExistingData(QString id)
{
    return {};
}

std::shared_ptr<Data> Backend::fetchNewData(DataRequest request)
{
    return apiCaller_->fetchData(request);
}

std::vector<std::shared_ptr<Data> > Backend::loadData(QString filepath)
{
    return {};
}

std::vector<std::shared_ptr<Data> > Backend::loadPreferences(QString filepath)
{
    return {};
}
