#include "apicallerfmi.hh"

const QString APICallerFMI::datetimeFormat = "yyyy-MM-dd'T'hh:mm':00Z'";

const QString APICallerFMI::baseURL_ = "http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=";

const QMap<QString,QMap<QString,QString>> APICallerFMI::requestParameters_{
    {"Temperature", {
            {"code","t2m"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::simple"},
            {"timestep", "30"}
        }},
    {"Average temperature", {
            {"code","tday"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::daily::simple"},
            {"timestep", "1440"}
        }},
    {"Average maximum temperature", {
            {"code","tmax"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::daily::simple"},
            {"timestep", "1440"}
        }},
    {"Average minimum temperature", {
            {"code","tmin"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::daily::simple"},
            {"timestep", "1440"}
        }},
    {"Observed wind", {
            {"code","ws_10min"},
            {"unit", "m/s"},
            {"query", "fmi::observations::weather::simple"},
            {"timestep", "30"}
        }},
    {"Observed cloudiness", {
            {"code","n_man"},
            {"unit", "okta"},
            {"query", "fmi::observations::weather::simple"},
            {"timestep", "30"}
        }},
    {"Predicted wind", {
            {"code","WindSpeedMS"},
            {"unit", "m/s"},
            {"query", "fmi::forecast::hirlam::surface::point::simple"},
            {"timestep", "30"}
        }},
    {"Predicted temperature", {
            {"code","Temperature"},
            {"unit", "celsius"},
            {"query", "fmi::forecast::hirlam::surface::point::simple"},
            {"timestep", "30"}
        }},
};

APICallerFMI::APICallerFMI(QObject *parent) : APICaller(parent)
{

}

void APICallerFMI::parse(QNetworkReply *reply)
{
    QXmlStreamReader xml;
    QByteArray answer = reply->readAll();
    xml.addData(answer);
    //after the download, read the data

    std::vector<QDateTime> dates;
    std::vector<qreal> values;
    std::vector<std::pair<QDateTime,qreal>> dataVector;

    while (!xml.atEnd()){
        xml.readNext();
        //qDebug()<<xml.name();
        if (xml.isStartElement()){
            if(xml.name() == "FeatureCollection"){
            }
            else if(xml.name() == "Time"){
                QString timeValue =  xml.readElementText();
                QDateTime dateTime = QDateTime::fromString(timeValue,datetimeFormat);
                dates.push_back(dateTime);
            }

            else if (xml.name() == "ParameterValue"){
                double value = xml.readElementText().toDouble();
                values.push_back(qreal(value));
            }
        }
    }

    if (xml.hasError()){
        qDebug() << "XML error: " << xml.errorString().data();
    }

    if(values.size() == 0){
        emit requestError(
                    QString("No data found! Try another "
                    "location or give a time range of at least %1 minutes.")
                    .arg(requestParameters_[dataRequest_.datatype]["timestep"])
                );
        return;
    }

    for (unsigned int i = 0; i < values.size();++i){
        if(qIsNaN(values[i]) || qIsInf(values[i])){
            continue;
        }
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],values[i]);
        dataVector.push_back(value);
    }

    if(dataRequest_.datatype == "Average temperature"
            || dataRequest_.datatype == "Average maximum temperature"
            || dataRequest_.datatype == "Average minimum temperature"){
        dataVector = calculateAverage(dataVector);
    }

    //qDebug() << answer;
    reply->deleteLater();

    auto data = std::make_shared<Data>(
                dataRequest_.datatype,
                requestParameters_[dataRequest_.datatype]["unit"],
                dataVector,
                dataRequest_.location);
    emit dataParsed(data);
}

QString APICallerFMI::formURL(DataRequest request)
{
    dataRequest_ = request;

    QString query = requestParameters_[dataRequest_.datatype]["query"];

    QString startTime = request.startTime.toString(datetimeFormat);

    QString endTime = request.endTime.toString(datetimeFormat);

    QString parameterUrl = QString("&place=%1&starttime=%2&endtime=%3&timestep=%4&parameters=%5")
            .arg(dataRequest_.location,startTime,endTime,
                 requestParameters_[dataRequest_.datatype]["timestep"],
                 requestParameters_[dataRequest_.datatype]["code"]);

    return baseURL_+ query + parameterUrl; //"fmi::observations::weather::simple&place=Pirkkala&starttime=2021-01-19T09:00:00Z&endtime=2021-01-24T14:00:00Z&timestep=30&parameters=t2m";
}

std::vector<std::pair<QDateTime, qreal> > APICallerFMI::calculateAverage(std::vector<std::pair<QDateTime, qreal> > &values)
{
    qreal sum = 0;
    qreal average = 0;

    std::vector<std::pair<QDateTime, qreal> > averageValues = {};

    for(auto pair : values){
        qreal value = pair.second;
        sum += value;
    }
    average = sum / values.size();

    averageValues.push_back(std::make_pair(values[0].first,average));
    averageValues.push_back(std::make_pair(values[values.size()-1].first,average));

    return averageValues;
}

void APICallerFMI::fetchData(DataRequest request)
{
    QNetworkRequest req = QNetworkRequest(formURL(request));

    //used to set the api key for requests
    //req.setRawHeader(QByteArray("x-api-key"),QByteArray(""));

    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &APICallerFMI::error);
}

QList<QString> APICallerFMI::dataTypes()
{
    return requestParameters_.keys();
}
