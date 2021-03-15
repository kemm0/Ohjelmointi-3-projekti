#include "view.hh"
#include <QDebug>

View::View(QObject* parent) :
    QObject{parent}
{
}

View::~View(){
}

void View::setChartData(QString chart_id, std::vector<std::shared_ptr<Data> > data)
{

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
