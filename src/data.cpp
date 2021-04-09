#include "data.hh"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtDebug>
#include <QXmlStreamReader>

int Data::idCounter = 0;

Data::Data(QString datatype, QString unit, dataVector dataValues, QObject *parent)
    : QObject(parent),
      id_(QString::number(idCounter++)),
      datatype_(datatype),
      unit_(unit),
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

dataVector Data::getDataValues()
{
    return dataValues_;
}

