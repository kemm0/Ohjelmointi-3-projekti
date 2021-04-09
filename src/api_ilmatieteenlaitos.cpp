#include "api_ilmatieteenlaitos.hh"

const QString API_Ilmatieteenlaitos::datetimeFormat = "yyyy-MM-dd'T'hh:mm':00Z'";

API_Ilmatieteenlaitos::API_Ilmatieteenlaitos(QObject *parent) : API(parent)
{
    baseURL_ = "http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=";
}

void API_Ilmatieteenlaitos::parse(QNetworkReply *reply)
{
    QXmlStreamReader xml;
    QByteArray answer = reply->readAll();
    xml.addData(answer);
    //after the download, read the data

    std::vector<QDateTime> dates;
    std::vector<qreal> temps;
    std::vector<std::pair<QDateTime,qreal>> values;

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
                temps.push_back(qreal(tempValue));
            }
        }
    }
    if (xml.hasError()){
        qDebug() << "XML error: " << xml.errorString().data();
    }

    for (unsigned int i = 0; i < temps.size();++i){
        if(qIsNaN(temps[i]) || qIsInf(temps[i])){
            continue;
        }
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],temps[i]);
        values.push_back(value);
    }

    //qDebug() << answer;
    reply->deleteLater();

    auto data = std::make_shared<Data>("Temperature", "Celsius", values, "Tampere");
    emit dataParsed(data);
}

QString API_Ilmatieteenlaitos::formURL(DataRequest request)
{
    QString startTime = request.startTime.toString(datetimeFormat);
    QString endTime = request.endTime.toString(datetimeFormat);
    QString parameterUrl = QString("fmi::observations::weather::simple&place=%1&starttime=%2&endtime=%3&timestep=30&parameters=t2m").arg(request.location,startTime,endTime);
    return baseURL_ + parameterUrl; //"fmi::observations::weather::simple&place=Pirkkala&starttime=2021-01-19T09:00:00Z&endtime=2021-01-24T14:00:00Z&timestep=30&parameters=t2m";
}
