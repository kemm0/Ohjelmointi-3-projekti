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
    auto series = dynamic_cast<QtCharts::QLineSeries*>(charts[chartIndex]->series()[0]);
    for(unsigned int i = 0; i < data.size(); i++){
        series->append(data[i].first.toMSecsSinceEpoch(),data[i].second);
    }
    auto axisList = charts[chartIndex]->series()[0]->attachedAxes();
    axisList[0]->setMin(data[0].first);
    axisList[0]->setMax(data[data.size()-1].first);
    std::vector<qreal> yValues = {};
    for(unsigned int i = 0; i < data.size(); i++){
        yValues.push_back(data.at(i).second);
        //qDebug()<<QString("%1 : %2").arg(data[i].first.toString(),QString::number(data[i].second));
    }
    qreal min = *std::min_element(yValues.begin(),yValues.end());
    qreal max = *std::max_element(yValues.begin(),yValues.end());

    axisList[1]->setMin(min);
    axisList[1]->setMax(max);
}

void View::removeChart(int index)
{

}

void View::clearChart(int index)
{
    try {
        for(unsigned int i = 0; i < charts[index]->series().length(); i++){
            delete charts[index]->series()[i];
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

void View::setProperties(QString dataType, QString startDate, QString startTime,
                         QString endDate, QString endTime,
                         bool showMonthlyAvg, bool showMonthlyMinMaxAvg)
{
    startTime_ = startTime_.fromString(startDate + ":" + startTime, "dd.MM.yyyy:hh:mm");
    endTime_ = endTime_.fromString(endDate + ":" + endTime, "dd.MM.yyyy:hh:mm");
    showMonthlyAvg_ = showMonthlyAvg;
    showMonthlyMinMaxAvg_ = showMonthlyMinMaxAvg;
    dataType_ = dataType;
    charts[currentChartIndex]->setTitle(dataType);
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
    auto axis = series->attachedAxes()[0];
    axis->setMin(startTime_);
    axis->setMax(endTime_);
    return charts.length() - 1;
}
