#include "apicallerfingrid.hh"


const QString APICallerFingrid::baseUrl_ = "https://api.fingrid.fi/v1/variable/%1/events/csv?start_time=%2&end_time=%3";
const QString APICallerFingrid::datetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00Z'";

const QMap<QString,QMap<QString,QString>> APICallerFingrid::requestParameters_{
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
        }},
    {"Power forms percentages", {}}
};

const QString APICallerFingrid::responseDatetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00+0000'";

APICallerFingrid::APICallerFingrid(QString apiKey, QObject *parent) :
    APICaller(parent),
    apiKey_(apiKey)
{
}

void APICallerFingrid::fetchData(DataRequest dataRequest)
{
    if(apiKey_ == ""){
        emit requestError(QString("API key missing! Define the API key in apiconfig.txt"));
        return;
    }

    if (dataRequest.datatype == "Power forms percentages") {
        handlePercentageRequest(dataRequest);
        handlingPercentageRequest = true;
    }
    else {

    //Create one API request based on the parameters in dataRequest
    QNetworkRequest req = QNetworkRequest(QString(formURL(dataRequest)));

    //sets the api key to the request header
    req.setRawHeader(QString("x-api-key").toUtf8(),QString(apiKey_).toUtf8());

    //the reply that was created from the request
    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &APICallerFingrid::error);
    }
}

QList<QString> APICallerFingrid::dataTypes()
{
    return requestParameters_.keys();
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
    if(dataVector.size() == 0){
        emit requestError(QString("No data found!"));
    }
    reply->deleteLater();

    // Create data object from the parsed data
    auto data = std::make_shared<Data>(
                dataRequest_.datatype,
                requestParameters_[dataRequest_.datatype]["unit"],
                dataVector,
                dataRequest_.location);

    if (handlingPercentageRequest){
        powerProductionValues.push_back(data);
        if (powerProductionValues.length() == 3) {
            countPercentages();
        }
    }
    else {
    emit dataParsed(data);
    }
}

QString APICallerFingrid::formURL(DataRequest dataRequest)
{
    dataRequest_ = dataRequest;
    QString startTime = dataRequest_.startTime.toString(datetimeFormat_);
    QString endTime = dataRequest_.endTime.toString(datetimeFormat_);
    QString requestUrl =  baseUrl_.arg(requestParameters_[dataRequest_.datatype]["id"],
            startTime,endTime);
    qDebug()<<requestUrl;
    return requestUrl;
}

void APICallerFingrid::handlePercentageRequest(DataRequest dataRequest)
{
    DataRequest windRequest = dataRequest;
    windRequest.datatype = "Wind power production";
    fetchData(windRequest);

    DataRequest hydroRequest = dataRequest;
    hydroRequest.datatype = "Hydro power production";
    fetchData(hydroRequest);

    DataRequest nuclearRequest = dataRequest;
    nuclearRequest.datatype = "Nuclear power production";
    fetchData(nuclearRequest);
}

void APICallerFingrid::countPercentages()
{

    for (auto power : powerProductionValues)
    {
        auto powerValues = power->getDataValues();
        for (unsigned long int i = 0; i < power->getDataValues().size(); i++)
        {
            powerValues[i].second = power->getDataValues()[i].second/(powerProductionValues[0]->getDataValues()[i].second +
                    powerProductionValues[1]->getDataValues()[i].second + powerProductionValues[2]->getDataValues()[i].second);
        }
        auto data = power;
        data->setDataValues(powerValues);
        emit dataParsed(data);
        powerValues.clear();
    }
    handlingPercentageRequest = false;
    powerProductionValues.clear();
}
