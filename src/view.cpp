#include "view.hh"
#include <QDebug>

View::View(QObject* parent) :
    QObject{parent},
    startTime_(QDateTime::currentDateTime())
{
        endTime_ = startTime_.addSecs(-7200);
}

View::~View(){
}

void View::setChartData(QString chart_id, std::vector<std::shared_ptr<Data> > data)
{
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

bool View::getShowMonthlyAvg()
{
    return showMonthlyAvg_;
}

bool View::getShowMonthlyMinMaxAvg()
{
    return showMonthlyMinMaxAvg_;
}

void View::setProperties(QString startDate, QString startTime, QString endDate, QString endTime,
                         bool showMonthlyAvg, bool showMonthlyMinMaxAvg)
{
    startTime_ = startTime_.fromString(startDate + ":" + startTime, "dd.MM.yyyy:hh:mm");
    endTime_ = endTime_.fromString(endDate + ":" + endTime, "dd.MM.yyyy:hh:mm");
    showMonthlyAvg_ = showMonthlyAvg;
    showMonthlyMinMaxAvg_ = showMonthlyMinMaxAvg;
}

void View::removeChart(QString chart_id)
{

}

void View::addChart(std::vector<std::shared_ptr<Data> > data)
{

}

void View::changeGridSize(int size)
{

}
