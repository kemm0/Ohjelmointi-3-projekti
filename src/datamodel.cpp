#include "datamodel.hh"

DataModel::DataModel(QObject *parent) : QObject(parent)
{

}

std::vector<std::shared_ptr<Data> > DataModel::getAllData()
{
    return dataVector;
}

qreal DataModel::getAverage(QString id)
{
    auto result = data.find(id);

    if (result == data.end()){
        return 0;
    }

    return 1;
}


