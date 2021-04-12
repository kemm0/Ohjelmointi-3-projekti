#include "apicallerfmi.hh"

const QString APICallerFMI::datetimeFormat = "yyyy-MM-dd'T'hh:mm':00Z'";

APICallerFMI::APICallerFMI(QObject *parent) : APICaller(parent)
{
    baseURL_ = "http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=";
    dataTypeParameters.insert("Temperature",{});
    dataTypeParameters["Temperature"].insert("code","t2m");
    dataTypeParameters["Temperature"].insert("unit","celsius");
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
                double tempValue = xml.readElementText().toDouble();
                values.push_back(qreal(tempValue));
            }
        }
    }
    if (xml.hasError()){
        qDebug() << "XML error: " << xml.errorString().data();
    }

    for (unsigned int i = 0; i < values.size();++i){
        if(qIsNaN(values[i]) || qIsInf(values[i])){
            continue;
        }
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],values[i]);
        dataVector.push_back(value);
    }

    //qDebug() << answer;
    reply->deleteLater();

    auto data = std::make_shared<Data>(
                dataRequest_.datatype,
                dataTypeParameters[dataRequest_.datatype]["unit"],
                dataVector,
                dataRequest_.location);
    emit dataParsed(data);
}

QString APICallerFMI::formURL(DataRequest request)
{
    dataRequest_ = request;
    QString startTime = request.startTime.toString(datetimeFormat);
    QString endTime = request.endTime.toString(datetimeFormat);
    QString parameterUrl = QString("fmi::observations::weather::simple&place=%1&starttime=%2&endtime=%3&timestep=30&parameters=%4")
            .arg(dataRequest_.location,startTime,endTime,dataTypeParameters[dataRequest_.datatype]["code"]);

    qDebug()<<"URL formed: " + baseURL_ + parameterUrl;
    return baseURL_ + parameterUrl; //"fmi::observations::weather::simple&place=Pirkkala&starttime=2021-01-19T09:00:00Z&endtime=2021-01-24T14:00:00Z&timestep=30&parameters=t2m";
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
