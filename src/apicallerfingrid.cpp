#include "apicallerfingrid.hh"


const QString APICallerFingrid::baseUrl_ = "https://api.fingrid.fi/v1/variable/%1/events/csv?start_time=%2&end_time=%3";
const QString APICallerFingrid::datetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00Z'";

const QMap<QString,QMap<QString,QString>> APICallerFingrid::requestParameters_{
    {"Electricity consumption", {
            {"id","124"},
            {"unit", "GW"}
        }},
    {"Electricity production", {
            {"id","74"},
            {"unit", "GW"}
        }},
    {"Electricity consumption forecast 24h", {
            {"id","165"},
            {"unit","GWh/h"}
        }},
    {"Electricity production forecast 24h", {
            {"id","242"},
            {"unit", "GW"}
        }},
    {"Wind power production", {
            {"id","181"},
            {"unit", "GW"}
        }},
    {"Nuclear power production", {
            {"id","188"},
            {"unit", "GW"}
        }},
    {"Hydro power production", {
            {"id","191"},
            {"unit", "GW"}
        }},
    {"Power forms percentages", {
            {"unit", "of total production (GW)"}
        }}
};

const QString APICallerFingrid::responseDatetimeFormat_ = "yyyy-MM-dd'T'hh:mm':00+0000'";

APICallerFingrid::APICallerFingrid(QString apiKey, QObject *parent) :
    APICaller(apiKey,parent),
    splitRequests_({}),
    dataVectors_({}),
    replies({}),
    requestSplit(false),
    requestCounter(0),
    requestFailed(false)
{
}

void APICallerFingrid::fetchData(DataRequest dataRequest)
{
    if(apiKey_ == ""){
        emit requestError(QString("API key missing! Define the API key in apiconfig.txt"));
        return;
    }

    qDebug()<<"Datarequest on fetch data: " + dataRequest.datatype;

    dataRequest_ = dataRequest;

    qDebug()<<"Fingrid data request: " + dataRequest.datatype;

    if (dataRequest.datatype == "Power forms percentages") {
        DataRequest windRequest = dataRequest;
        windRequest.datatype = "Wind power production";
        createNetworkRequest(windRequest);

        DataRequest hydroRequest = dataRequest;
        hydroRequest.datatype = "Hydro power production";
        createNetworkRequest(hydroRequest);

        DataRequest nuclearRequest = dataRequest;
        nuclearRequest.datatype = "Nuclear power production";
        createNetworkRequest(nuclearRequest);
    }
    else {
        createNetworkRequest(dataRequest);
    }
}

QList<QString> APICallerFingrid::dataTypes()
{
    return requestParameters_.keys();
}

void APICallerFingrid::parse(QNetworkReply *reply)
{
    if(requestFailed){
        return;
    }
    std::vector<QDateTime> dates;
    std::vector<qreal> values;

    QTextStream stream(reply->readAll());

    int requestID = reply->property("requestID").toInt();

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
        dataVectors_[requestID].push_back(value);
    }
    if(dataVectors_[requestID].size() == 0){
        emit requestError(QString("No data found with these parameters!"));
        requestFailed = true;
        return;
    }

    reply->setProperty("parsingFinished",true);

    bool allRepliesFinished = true;

    for(int i = 0; i < replies.size(); i++){
        bool replyFinished = replies[i]->property("parsingFinished").toBool();
        if(replyFinished == false){
            allRepliesFinished = false;
        }
    }

    if(allRepliesFinished){
        qDebug()<<"datarequest datatype: " + dataRequest_.datatype;
        // Create data object from the parsed data
        if(dataRequest_.datatype == "Power forms percentages"){
            calculatePercentages();
        }
        for(auto requestID : splitRequests_.keys()){
            auto dataRequest = splitRequests_[requestID];
            auto data = std::make_shared<Data>(
                        dataRequest.datatype,
                        requestParameters_[dataRequest_.datatype]["unit"],
                        dataRequest.location,
                        dataRequest_.dataSource);
            data->setDataValues(dataVectors_[requestID]);
            emit dataParsed(data);
        }
        for(auto networkReply : replies){
            networkReply->deleteLater();
        }
    }
}

QString APICallerFingrid::formURL(DataRequest dataRequest)
{
    QString startTime = dataRequest.startTime.toString(datetimeFormat_);
    QString endTime = dataRequest.endTime.toString(datetimeFormat_);
    QString requestUrl =  baseUrl_.arg(requestParameters_[dataRequest.datatype]["id"],
            startTime,endTime);
    qDebug()<<requestUrl;
    return requestUrl;
}

void APICallerFingrid::calculatePercentages()
{
    /**for(auto &dataVector : dataVectors_){ // percentages over the whole time
        double vectorSum = 0;
        QDateTime startTime = dataVector[0].first;
        QDateTime endTime = dataVector[dataVector.size() -1].first;
        for(auto &pair : dataVector){
            qDebug()<<QString::number(counter) + " : " + pair.first.toString() + " : " + QString::number(pair.second);
            vectorSum += pair.second;
        }
        total += vectorSum;
        dataVector.clear();
        dataVector.push_back(std::make_pair(startTime,vectorSum));
        dataVector.push_back(std::make_pair(endTime,vectorSum));
    }
    for(auto &dataVector : dataVectors_){
        auto startValue = dataVector[0].second;
        auto endValue = dataVector[dataVector.size()-1].second;
        dataVector[0].second = startValue / total;
        dataVector[dataVector.size()-1].second = endValue / total;
        qDebug()<< startValue << " " << endValue;
    }**/
    for (uint i = 0 ; i < dataVectors_.first().size(); i++){
        auto &date = dataVectors_.first()[i].first;
        double total = 0;
        auto dataRequestIDs = dataVectors_.keys();
        for(auto requestID : dataRequestIDs){
            auto &pair = dataVectors_[requestID][i];
            try{
                if(pair.first != date){
                    break;
                }
                total += pair.second;
            }
            catch(std::out_of_range const& exc){
                break;
            }
        }
        for(auto requestID : dataRequestIDs){
            auto &pair = dataVectors_[requestID][i];
            try{
                if(pair.first != date){
                    break;
                }
                pair.second = pair.second / total;
            }
            catch(std::out_of_range const& exc){
                break;
            }
        }
    }
}

void APICallerFingrid::createNetworkRequest(DataRequest &request)
{
    //Create one API request based on the parameters in dataRequest
    QNetworkRequest req = QNetworkRequest(QString(formURL(request)));

    //sets the api key to the request header
    req.setRawHeader(QString("x-api-key").toUtf8(),QString(apiKey_).toUtf8());

    requestCounter++;

    //the reply that was created from the request
    QNetworkReply *reply = manager_->get(req);
    reply->setProperty("requestID",requestCounter);
    reply->setProperty("parsingFinished", false);
    splitRequests_.insert(requestCounter,request);
    dataVectors_[requestCounter] = {};

    replies.append(reply);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &APICallerFingrid::error);
}
