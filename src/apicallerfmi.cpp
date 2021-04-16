#include "apicallerfmi.hh"
#include <cmath>

const QString APICallerFMI::datetimeFormat = "yyyy-MM-dd'T'hh:mm':00Z'";

const QString APICallerFMI::baseURL_ = "http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=";

const QMap<QString,QMap<QString,QString>> APICallerFMI::requestParameters_{
    {"Temperature", {
            {"code","t2m"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::simple"},
            {"maxRequestRange", "7"},
            {"timestep", "30"},
            {"type", "observation"}
        }},
    {"Average temperature", {
            {"code","tday"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::daily::simple"},
            {"maxRequestRange", "360"},
            {"timestep", "1440"},
            {"type", "average"}
        }},
    {"Average maximum temperature", {
            {"code","tmax"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::daily::simple"},
            {"maxRequestRange", "360"},
            {"timestep", "1440"},
            {"type", "average"}
        }},
    {"Average minimum temperature", {
            {"code","tmin"},
            {"unit", "celsius"},
            {"query", "fmi::observations::weather::daily::simple"},
            {"maxRequestRange", "360"},
            {"timestep", "1440"},
            {"type", "average"}
        }},
    {"Observed wind", {
            {"code","ws_10min"},
            {"unit", "m/s"},
            {"query", "fmi::observations::weather::simple"},
            {"maxRequestRange", "7"},
            {"timestep", "30"},
            {"type", "observation"}
        }},
    {"Observed cloudiness", {
            {"code","n_man"},
            {"unit", "okta"},
            {"query", "fmi::observations::weather::simple"},
            {"maxRequestRange", "7"},
            {"timestep", "30"},
            {"type", "observation"}
        }},
    {"Predicted wind", {
            {"code","WindSpeedMS"},
            {"unit", "m/s"},
            {"query", "fmi::forecast::hirlam::surface::point::simple"},
            {"maxRequestRange", "7"},
            {"timestep", "30"},
            {"type", "forecast"}
        }},
    {"Predicted temperature", {
            {"code","Temperature"},
            {"unit", "celsius"},
            {"query", "fmi::forecast::hirlam::surface::point::simple"},
            {"maxRequestRange", "7"},
            {"timestep", "30"},
            {"type", "forecast"}
        }},
};

APICallerFMI::APICallerFMI(QObject *parent) :
    APICaller(parent),
    requestSplit(false),
    splitRequests_({})
{

}

void APICallerFMI::parse(QNetworkReply *reply)
{
    DataRequest request = splitRequests_[reply->property("requestID").toInt()];
    qDebug()<< request;
    QXmlStreamReader xml;
    QByteArray answer = reply->readAll();
    xml.addData(answer);
    //after the download, read the data

    std::vector<QDateTime> dates;
    std::vector<qreal> values;

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
                    .arg(requestParameters_[request.datatype]["timestep"])
                );
        return;
    }

    for (unsigned int i = 0; i < values.size();++i){
        if(qIsNaN(values[i]) || qIsInf(values[i])
                || !dates[i].isValid()){
            continue;
        }
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],values[i]);
        dataVector.push_back(value);
    }

    reply->setProperty("parsingFinished",true);

    bool allRepliesFinished = true;

    for(int i = 0; i < replies.size(); i++){
        bool replyFinished = replies[i]->property("parsingFinished").toBool();
        if(replyFinished == false){
            allRepliesFinished = false;
        }
    }
    qDebug()<<allRepliesFinished;

    if(allRepliesFinished){
        if(requestParameters_[request.datatype]["type"] == "average"){
            dataVector = calculateAverage(dataVector);
        }
        if(requestSplit){
            std::sort(dataVector.begin(),dataVector.end(), []
                      (std::pair<QDateTime,qreal> a, std::pair<QDateTime,qreal> b){
                return a.first < b.first;
            });
        }

        auto data = std::make_shared<Data>(
                    request.datatype,
                    requestParameters_[request.datatype]["unit"],
                    dataVector,
                    request.location);
        for(int i = 0; i < replies.size(); i++){
            auto r = replies.at(i);
            r->deleteLater();
        }
        emit dataParsed(data);
    }

    //auto data = createDataObject(dataVector,requestParameters_[request.datatype]["unit"]);
}

QString APICallerFMI::formURL(DataRequest request)
{
    QString query = requestParameters_[request.datatype]["query"];

    QString startTime = request.startTime.toString(datetimeFormat);

    QString endTime = request.endTime.toString(datetimeFormat);

    QString parameterUrl = QString("&place=%1&starttime=%2&endtime=%3&timestep=%4&parameters=%5")
            .arg(request.location,startTime,endTime,
                 requestParameters_[request.datatype]["timestep"],
                 requestParameters_[request.datatype]["code"]);

    qDebug()<< baseURL_+ query + parameterUrl;

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

QMap<int, DataRequest> APICallerFMI::splitDataRequest(DataRequest &request, int &splitFactor)
{
    int replyIdCounter = 0;
    int splits = request.startTime.daysTo(request.endTime) / splitFactor;

    QMap<int, DataRequest> splitRequests = {};

    if(splits >= 1){
        requestSplit = true;
        QDateTime splitStartTime = request.startTime;
        while(splits >= 0){
            DataRequest splitRequest = request;
            splitRequest.startTime = splitStartTime;
            if(splitRequest.startTime.addDays(splitFactor) > request.endTime){
                splitRequest.endTime = request.endTime;
            }
            else{
                splitRequest.endTime = splitStartTime.addDays(splitFactor);
                splitStartTime = splitStartTime.addDays(splitFactor);
            }
            replyIdCounter++;
            splitRequests[replyIdCounter] = splitRequest;
            splits -= 1;
        }
    }
    else{
        splitRequests[replyIdCounter] = request;
    }

    return splitRequests;
}

void APICallerFMI::fetchData(DataRequest request)
{
    dataRequest_ = request;

    int maxRequestRange =
            requestParameters_[request.datatype]["maxRequestRange"].toInt();

    splitRequests_ = splitDataRequest(request,maxRequestRange);

    for(const auto key : splitRequests_.keys()){
        QNetworkRequest req = QNetworkRequest(formURL(splitRequests_[key]));

        QNetworkReply *reply = manager_->get(req);

        reply->setProperty("requestID", key);
        reply->setProperty("parsingFinished", false);

        replies.append(reply);

        //connect to error slot if error signaled
        connect(reply, &QNetworkReply::errorOccurred, this, &APICallerFMI::error);
    }
}

QList<QString> APICallerFMI::dataTypes()
{
    return requestParameters_.keys();
}
