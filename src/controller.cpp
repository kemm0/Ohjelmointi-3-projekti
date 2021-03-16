#include "controller.hh"
#include "DataRequest.h"


Controller::Controller(std::shared_ptr<Backend> backend, std::shared_ptr<View> view, QObject *parent)
    : QObject(parent),
      backend_{backend},
      view_{view}
{

}

void Controller::getNewData()
{
    qDebug()<<"new data fetched";
}

void  Controller::getExistingData()
{
}

void Controller::loadData()
{
}

void Controller::loadPreferences()
{
}
