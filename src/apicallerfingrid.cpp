#include "apicallerfingrid.hh"

const QString APICallerFingrid::API_KEY = "";


const QString APICallerFingrid::baseUrl_ = "https://api.fingrid.fi/v1/variable/%1/events/csv?start_time=%2&end_time=%3";
const QString APICallerFingrid::datetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00Z'";

const QMap<QString,QMap<QString,QString>> APICallerFingrid::dataRequestParameters{
    {"Electricity consumption", {
            {"id","124"},
            {"unit", "GWh/h"}
        }},
    {"Electricity production", {
            {"id","74"},
            {"unit", "GWh/h"}
        }},
    {"Electricity consumption forecast 24h", {
            {"id","165"},
            {"unit","GWh/h"}
        }},
    {"Electricity production forecast 24h", {
            {"id","242"},
            {"unit", "GWh/h"}
        }},
    {"Wind power production", {
            {"id","75"},
            {"unit", "GWh/h"}
        }},
    {"Nuclear power production", {
            {"id","188"},
            {"unit", "GW"}
        }},
    {"Hydro power production", {
            {"id","191"},
            {"unit", "GW"}
        }}
};

const QString APICallerFingrid::responseDatetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00+0000'";

APICallerFingrid::APICallerFingrid(QObject *parent) : APICaller(parent)
{
}

void APICallerFingrid::fetchData(DataRequest dataRequest)
{
    if(API_KEY == ""){
        emit requestError(QString("API key missing! Define the API key in apicallerfingrid.cpp"));
        return;
    }

    //Create one API request based on the parameters in dataRequest
    QNetworkRequest req = QNetworkRequest(QString(formURL(dataRequest)));

    //sets the api key to the request header
    req.setRawHeader(QString("x-api-key").toUtf8(),QString(API_KEY).toUtf8());

    //the reply that was created from the request
    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &APICallerFingrid::error);
}

QList<QString> APICallerFingrid::dataTypes()
{
    return dataRequestParameters.keys();
}

void APICallerFingrid::parse(QNetworkReply *reply)
{
    std::vector<QDateTime> dates;
    std::vector<qreal> values;
    std::vector<std::pair<QDateTime,qreal>> dataVector;

    QTextStream stream(reply->readAll());

    //Read the reply and parse data
    while (!stream.atEnd()){

      QString line = stream.readLine();

      auto elements = line.split(",");

      if(elements[0] == "start_time"){
          continue;
      }
      QDateTime date = QDateTime::fromString(elements[0],responseDatetimeFormat_);

      qreal value = elements[2].toDouble()/1000; // Convert MWh to GWh

      dates.push_back(date);
      values.push_back(value);
    }
    for (unsigned int i = 0; i < values.size();++i){
        if(qIsNaN(values[i]) || qIsInf(values[i])){ //skip NaN values
            continue;
        }
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],values[i]);
        dataVector.push_back(value);
    }
    reply->deleteLater();

    // Create data object from the parsed data
    auto data = std::make_shared<Data>(
                dataRequest_.datatype,
                dataRequestParameters[dataRequest_.datatype]["unit"],
                dataVector,
                dataRequest_.location);

    emit dataParsed(data);
}

QString APICallerFingrid::formURL(DataRequest dataRequest)
{
    dataRequest_ = dataRequest;
    QString startTime = dataRequest_.startTime.toString(datetimeFormat_);
    QString endTime = dataRequest_.endTime.toString(datetimeFormat_);
    QString requestUrl =  baseUrl_.arg(dataRequestParameters[dataRequest_.datatype]["id"],
            startTime,endTime);
    qDebug()<<requestUrl;
    return requestUrl;
}
