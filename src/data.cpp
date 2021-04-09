#include "data.hh"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtDebug>
#include <QXmlStreamReader>

int Data::idCounter = 0;

Data::Data(QString datatype, QString unit, dataVector dataValues, QString location, QObject *parent)
    : QObject(parent),
      id_(QString::number(idCounter++)),
      datatype_(datatype),
      unit_(unit),
      location_(location),
      dataValues_(dataValues)
{

}

Data::~Data()
{

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

QString Data::getLocation()
{
    return location_;
}

dataVector Data::getDataValues()
{
    return dataValues_;
}

