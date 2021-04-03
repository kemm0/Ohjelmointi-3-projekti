#include "controller.hh"
#include "DataRequest.h"


void Controller::sendDataToView(std::vector<std::pair<QDateTime, qreal> > data)
{

}

Controller::Controller(std::shared_ptr<Backend> backend, std::shared_ptr<View> view, QObject *parent)
    : QObject(parent),
      backend_{backend},
      view_{view}
{
}

void Controller::getNewData()
{
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
