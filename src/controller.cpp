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
    DataRequest request;
    request.startTime = view_->getStartTime();
    request.endTime = view_->getEndTime();
    request.datatype = view_->getDataType();
    request.showMonthlyAvg = view_->getShowMonthlyAvg();
    request.showMonthlyMinMaxAvg = view_->getShowMonthlyMinMaxAvg();
    backend_->fetchNewData(request);
    qDebug()<<"data Request sent";
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
