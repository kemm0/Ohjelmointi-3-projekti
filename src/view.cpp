#include "view.hh"
#include <QDebug>
#include <QString>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QLineSeries>

View::View(QObject* parent) :
    QObject{parent}
{
}

View::~View(){

}
