#include "view.hh"
#include <QDebug>

View::View(QObject* parent) :
    QObject{parent},
    lineSeries_{},
    startTime_(QDateTime::currentDateTime()) {
        endTime_ = startTime_.addSecs(-7200);
}

View::~View(){
    if(lineSeries_){
        delete lineSeries_;
    }
}

QString View::getStartDateValue()
{
    return startTime_.toString("dd.MM.yyyy");
}

QString View::getStartTimeValue()
{
    return startTime_.toString("hh:mm");
}

QString View::getEndDateValue()
{
    return endTime_.toString("dd.MM.yyyy");
}

QString View::getEndTimeValue()
{
    return endTime_.toString("hh:mm");
}

void View::setTime(QString startDate, QString startTime, QString endDate, QString endTime)
{
    startTime_ = startTime_.fromString(startDate + ":" + startTime, "dd.MM.yyyy:hh:mm");
    endTime_ = endTime_.fromString(endDate + ":" + endTime, "dd.MM.yyyy:hh:mm");
}

QtCharts::QLineSeries* View::getLineSeries() const{
    return lineSeries_;
}

void View::setLineSeries(QtCharts::QLineSeries *lineSeries){
    if (lineSeries_ == lineSeries) return;
    if (lineSeries_ && lineSeries_->parent() == this) delete lineSeries_;
    lineSeries_ = lineSeries;
    emit lineSeriesSignal();
}

void View::setData(std::vector<std::pair<QDateTime,qreal>> data ){
    if (lineSeries_)
    {
        lineSeries_->clear();
        qreal max = data[0].second;
        qreal min = data[1].second;

        for(unsigned int i = 0; i < data.size(); i++){
            lineSeries_->append(i,data[i].second);
            if(data[i].second > max){
                max = data[i].second;
            }
            if(data[i].second < min){
                min = data[i].second;
            }
        }
        int size = data.size();

        lineSeries_->attachedAxes()[0]->setMax(size);
        lineSeries_->attachedAxes()[1]->setMax(max);
        lineSeries_->attachedAxes()[1]->setMin(min);
    }
}

void View::clearData(){
    if (lineSeries_)
    {
        lineSeries_->clear();
    }
}
