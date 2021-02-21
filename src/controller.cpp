#include "controller.hh"

Controller::Controller(Data* data,
                       View* view,
                       QObject *parent) :
    QObject(parent),
    data_{data},
    view_{view}
{

}

void Controller::fetchData()
{
    auto data = data_->getValues();
    view_->setData(data);
}
