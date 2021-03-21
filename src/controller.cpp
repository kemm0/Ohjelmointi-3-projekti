#include "controller.hh"
#include "DataRequest.h"


void Controller::sendDataToView(std::vector<std::pair<QDateTime, qreal> > data)
{
    view_->addChartData(view_->getCurrentChartIndex(),data);
    //for(unsigned int i = 0; i < data.size();i++){
        //qDebug()<<data[i].second;
    //}
    qDebug()<<"Data saved to view";
}

Controller::Controller(std::shared_ptr<Backend> backend, std::shared_ptr<View> view, QObject *parent)
    : QObject(parent),
      backend_{backend},
      view_{view}
{
    connect(backend_.get(),&Backend::requestComplete,this, &Controller::sendDataToView);
}

void Controller::getNewData()
{
    DataRequest request;
    request.id = view_->getCurrentChartIndex();
    request.startTime = view_->getStartTime();
    request.endTime = view_->getEndTime();
    request.datatype = view_->getDataType();
    request.showMonthlyAvg = view_->getShowMonthlyAvg();
    request.showMonthlyMinMaxAvg = view_->getShowMonthlyMinMaxAvg();
    request.location = view_->getLocation();
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
