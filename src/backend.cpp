#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{

}

std::map<QString, std::vector<std::shared_ptr<Data> > > Backend::getExistingData(QString id)
{
    return {};
}

std::vector<std::shared_ptr<Data> > Backend::fetchNewData(DataRequest request)
{
    return {};
}

std::vector<std::shared_ptr<Data> > Backend::loadData(QString filepath)
{
    return {};
}

std::vector<std::shared_ptr<Data> > Backend::loadPreferences(QString filepath)
{
    return {};
}
