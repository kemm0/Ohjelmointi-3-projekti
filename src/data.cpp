#include "data.hh"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtDebug>
#include <QXmlStreamReader>

Data::Data(QObject *parent):
    QObject(parent),
    id_(""),
    datatype_(""),
    unit_(""),
    dataValues_({}),
    monthlyAvg_({}),
    monthlyMinMaxAvg_({})
{

}

void Data::setData(QString id, QString datatype, QString unit, dataVector dataValues)
{
    id_ = id;
    datatype_ = datatype;
    unit_ = unit;
    dataValues_ = dataValues;

}

QString Data::getId()
{
    return id_;
}

QString Data::getDatatype()
{
    return datatype_;
}

QString Data::getUnit()
{
    return unit_;
}

dataVector Data::getDataValues()
{
    return dataValues_;
}
