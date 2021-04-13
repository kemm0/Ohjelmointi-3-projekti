#include "data.hh"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtDebug>
#include <QXmlStreamReader>
#include <QJsonArray>

int Data::idCounter = 0;
const QString Data::jsonDateTimeFormat = "yyyy-MM-dd'T'hh:mm:'00.000'";

Data::Data(QString datatype, QString unit, dataVector dataValues, QString location, QObject *parent)
    : QObject(parent),
      id_(QString::number(idCounter++)),
      datatype_(datatype),
      unit_(unit),
      location_(location),
      dataValues_(dataValues)
{

}

Data::Data(QObject *parent) :
    QObject(parent),
    id_(QString::number(idCounter++)),
    datatype_(""),
    unit_(""),
    location_(""),
    dataValues_({})
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

Data *Data::fromJSON(QJsonObject &document)
{
    Data* newData = new Data();

    QString datatype = document["datatype"].toString();
    QString unit = document["unit"].toString();
    QString location = document["location"].toString();

    newData->setDatatype(datatype);
    newData->setUnit(unit);
    newData->setLocation(location);

    QJsonArray jsonDates = document["dates"].toArray();
    QJsonArray jsonValues = document["values"].toArray();

    std::vector<std::pair<QDateTime,qreal>> dataVector = {};

    for(int i = 0; i < jsonDates.size(); i++){
        QString dateString = jsonDates[i].toString();
        QDateTime datetime = QDateTime::fromString(dateString,jsonDateTimeFormat);
        qreal value = jsonValues[i].toDouble();

        dataVector.push_back(std::make_pair(datetime,value));
    }
    newData->setDataValues(dataVector);
    return newData;
}

QJsonObject Data::toJSON()
{
    QJsonObject jsonObject;
    jsonObject.insert("datatype",datatype_);
    jsonObject.insert("unit",unit_);
    jsonObject.insert("location",location_);
    QJsonArray dates;
    QJsonArray values;
    for(uint i = 0; i < dataValues_.size(); i++){
        dates.append(QJsonValue::fromVariant((dataValues_.at(i).first)));
        values.append(QJsonValue::fromVariant((dataValues_.at(i).second)));
    }
    jsonObject.insert("dates",dates);
    jsonObject.insert("values",values);

    return jsonObject;
}

void Data::setDatatype(QString &datatype)
{
    datatype_ = datatype;
}

void Data::setUnit(QString &unit)
{
    unit_ = unit;
}

void Data::setLocation(QString &location)
{
    location_ = location;
}

void Data::addDataValues(dataVector &dataValues)
{
    for(uint i = 0; i < dataValues.size(); i++){
        dataValues_.push_back(dataValues[i]);
    }
}

void Data::setDataValues(dataVector &dataValues)
{
    dataValues_ = dataValues;
}

void Data::print()
{
    qDebug()<< "Printing data id: " + id_;
    qDebug()<< "Datatype: " << datatype_ << "Unit: " << unit_ << "Location: " << location_;
    qDebug()<< "Data values:";
    for(uint i = 0; i < dataValues_.size(); i++){
        qDebug()<< "Datetime: " << dataValues_[i].first << "Value: " << dataValues_[i].second;
    }
    qDebug()<< "End of data print id: " + id_;
}

