#include "controller.hh"

Controller::Controller(std::shared_ptr<Data> data,
                       QObject *parent) :
    QObject(parent),
    data_{data}
{

}

void Controller::fetchData()
{

}
