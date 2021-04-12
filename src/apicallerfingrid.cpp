#include "apicallerfingrid.hh"

const QString APICallerFingrid::API_KEY = "";


const QString APICallerFingrid::baseUrl_ = "https://api.fingrid.fi/v1/variable/%1/events/csv?start_time=%2&end_time=%3";
const QString APICallerFingrid::datetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00Z'";
const QVector<QString> APICallerFingrid::datatypes_ = {
    "Electricity consumption","Electricity production", "Electricity consumption forecast 24h",
    "Electricity production forecast 24h", "Wind power production", "Nuclear power production",
    "Hydro power production", "Power forms percentages"
};

const QString APICallerFingrid::responseDatetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00+0000'";

APICallerFingrid::APICallerFingrid(QObject *parent) : APICaller(parent)
{
    dataTypeParameters["Electricity consumption"].insert("id","124");
    dataTypeParameters["Electricity consumption"].insert("unit","GWh/h");
    dataTypeParameters["Electricity production"].insert("id","74");
    dataTypeParameters["Electricity production"].insert("unit","GWh/h");
    dataTypeParameters["Electricity consumption forecast 24h"].insert("id","165");
    dataTypeParameters["Electricity consumption forecast 24h"].insert("unit","GWh/h");
    dataTypeParameters["Electricity production forecast 24h"].insert("id","242");
    dataTypeParameters["Electricity production forecast 24h"].insert("unit","GWh/h");
    dataTypeParameters["Wind power production"].insert("id","75");
    dataTypeParameters["Wind power production"].insert("unit","GWh/h");
    dataTypeParameters["Nuclear power production"].insert("id","188");
    dataTypeParameters["Nuclear power production"].insert("unit","GW");
    dataTypeParameters["Hydro power production"].insert("id","191");
    dataTypeParameters["Hydro power production"].insert("unit","GW");
}

void APICallerFingrid::fetchData(DataRequest dataRequest)
{
    if(API_KEY == ""){
        qDebug()<<"API key missing! Define the API key in apicallerfingrid.cpp";
        return;
    }

    QNetworkRequest req = QNetworkRequest(QString(formURL(dataRequest)));
    req.setRawHeader(QString("x-api-key").toUtf8(),QString(API_KEY).toUtf8());

    //used to set the api key for requests
    //req.setRawHeader(QByteArray("x-api-key"),QByteArray(""));

    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &APICallerFingrid::error);
}

QVector<QString> APICallerFingrid::dataTypes()
{
    return datatypes_;
}

void APICallerFingrid::parse(QNetworkReply *reply)
{
    std::vector<QDateTime> dates;
    std::vector<qreal> values;
    std::vector<std::pair<QDateTime,qreal>> dataVector;
    QTextStream stream(reply->readAll());
    while (!stream.atEnd()){
      QString line = stream.readLine();
      auto elements = line.split(",");
      if(elements[0] == "start_time"){
          continue;
      }
      QDateTime date = QDateTime::fromString(elements[0],responseDatetimeFormat_);
      qreal value = elements[2].toDouble()/1000;
      dates.push_back(date);
      values.push_back(value);
    }
    for (unsigned int i = 0; i < values.size();++i){
        if(qIsNaN(values[i]) || qIsInf(values[i])){
            continue;
        }
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],values[i]);
        dataVector.push_back(value);
    }
    reply->deleteLater();

    auto data = std::make_shared<Data>(
                dataRequest_.datatype,
                dataTypeParameters[dataRequest_.datatype]["unit"],
                dataVector,
                dataRequest_.location);
    emit dataParsed(data);
}

QString APICallerFingrid::formURL(DataRequest dataRequest)
{
    dataRequest_ = dataRequest;
    QString startTime = dataRequest_.startTime.toString(datetimeFormat_);
    QString endTime = dataRequest_.endTime.toString(datetimeFormat_);
    QString requestUrl =  baseUrl_.arg(dataTypeParameters[dataRequest_.datatype]["id"],
            startTime,endTime);
    qDebug()<<requestUrl;
    return requestUrl;
}
