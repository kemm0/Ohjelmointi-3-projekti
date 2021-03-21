#include "view.hh"
#include <QDebug>
#include <QString>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QLineSeries>

View::View(QObject* parent) :
    QObject{parent},
    startTime_(QDateTime::currentDateTime().addSecs(-7200*4)),
    endTime_(QDateTime::currentDateTime())
{
        charts = {};
}

View::~View(){

}

void View::addChartData(int chartIndex, std::vector<std::pair<QDateTime, qreal>> data)
{
    // Jostain syystä x-akselin muuttuessa vanhat lineseriesit ei näy oikein. Pitää muuttaa jokaisen lineseriesin akseleita erikseen?

    auto series = new QtCharts::QLineSeries();
    for(unsigned int i = 0; i < data.size(); i++){
        series->append(data[i].first.toMSecsSinceEpoch(),data[i].second);
    }
    auto chartXAxis = dynamic_cast<QtCharts::QDateTimeAxis*>(charts[chartIndex]->axisX());
    auto chartYAxis = dynamic_cast<QtCharts::QValueAxis*>(charts[chartIndex]->axisY());

    if(data[0].first < chartXAxis->min()){
        chartXAxis->setMin(data[0].first);
    }
    if(data[data.size()-1].first > chartXAxis->max()){
        chartXAxis->setMax(data[data.size()-1].first);
    }

    std::vector<qreal> yValues = {};
    for(unsigned int i = 0; i < data.size(); i++){
        yValues.push_back(data.at(i).second);
    }
    qreal min = *std::min_element(yValues.begin(),yValues.end());
    qreal max = *std::max_element(yValues.begin(),yValues.end());
    if(min < chartYAxis->min()){
        chartYAxis->setMin(min);
    }
    if(max > chartYAxis->max()){
        chartYAxis->setMax(max);
    }

    charts[chartIndex]->addSeries(series);
    series->setName(QString("%1 (%2)").arg(dataType_,location_));

    auto chartSeries = charts[chartIndex]->series();

    for(auto &series : chartSeries){
        if(series->attachedAxes().isEmpty()){
            series->attachAxis(chartXAxis);
            series->attachAxis(chartYAxis);
        }
    }
}

void View::setChartData(int chartIndex, std::vector<std::vector<std::pair<QDateTime, qreal> > > data)
{
    auto oldSeriesList = charts[chartIndex]->series();
    for(int i = 0; i < oldSeriesList.size(); i++){
        delete oldSeriesList[i];
    }

    auto xAxis = charts[chartIndex]->axisX();
    auto yAxis = charts[chartIndex]->axisY();

    for(unsigned int i = 0; i < data.size(); i++){
        auto series = new QtCharts::QLineSeries();
        for(unsigned int j = 0; j < data[i].size(); j++){
            series->append(data[i][j].first.toMSecsSinceEpoch(),data[i][j].second);
        }
        xAxis->setMin(data[i][0].first);
        xAxis->setMax(data[i][data[i].size()-1].first);

        std::vector<qreal> yValues = {};
        for(unsigned int j = 0; j < data[i].size(); j++){
            yValues.push_back(data[i][j].second);
        }
        qreal min = *std::min_element(yValues.begin(),yValues.end());
        qreal max = *std::max_element(yValues.begin(),yValues.end());
        yAxis->setMin(min);
        yAxis->setMax(max);
        series->setName(QString("%1 (%2)").arg(dataType_,location_));
        charts[chartIndex]->addSeries(series);
    }
}

void View::removeChart(int chartIndex)
{

}

void View::clearChart(int chartIndex)
{
    try {
        for(auto& series: charts[chartIndex]->series()){
            delete series;
        }
    }  catch (...) {
        qDebug()<<"Ei voi clearata ;(";
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

bool View::getShowMonthlyAvg()
{
    return showMonthlyAvg_;
}

bool View::getShowMonthlyMinMaxAvg()
{
    return showMonthlyMinMaxAvg_;
}

QString View::getDataType()
{
    return dataType_;
}

QDateTime View::getStartTime()
{
    return startTime_;
}

QDateTime View::getEndTime()
{
    return endTime_;
}

int View::getCurrentChartIndex() const
{
    return currentChartIndex;
}

void View::setCurrentChartIndex(int value)
{
    currentChartIndex = value;
}

QString View::getLocation() const
{
    return location_;
}

void View::setLocation(const QString &location)
{
    location_ = location;
}

void View::setProperties(QString dataType, QString location, QString startDate, QString startTime,
                         QString endDate, QString endTime,
                         bool showMonthlyAvg, bool showMonthlyMinMaxAvg)
{
    startTime_ = startTime_.fromString(startDate + ":" + startTime, "dd.MM.yyyy:hh:mm");
    endTime_ = endTime_.fromString(endDate + ":" + endTime, "dd.MM.yyyy:hh:mm");
    location_ = location;
    showMonthlyAvg_ = showMonthlyAvg;
    showMonthlyMinMaxAvg_ = showMonthlyMinMaxAvg;
    dataType_ = dataType;
    //qDebug()<<currentChartIndex;
}

int View::setChartFromSeries(int index, QtCharts::QLineSeries *series)
{
    try {
        charts[index] = series->chart();
        return index;
    }  catch (...) {
        charts.append(series->chart());
        return charts.length() - 1;
    }
}

int View::addChartFromSeries(QtCharts::QLineSeries *series)
{
    charts.append(series->chart());
    charts[charts.length()-1]->series()[0]->setName("Data " + QString::number(charts.length()));
    charts[charts.length()-1]->axisX()->setMin(startTime_);
    charts[charts.length()-1]->axisX()->setMin(endTime_);
    for(auto& series: charts[charts.length()-1]->series()){
        delete series;
    }
    return charts.length() - 1;
}
