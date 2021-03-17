#include "api_ilmatieteenlaitos.hh"

API_Ilmatieteenlaitos::API_Ilmatieteenlaitos(QObject *parent) : API(parent)
{

}

std::shared_ptr<Data> API_Ilmatieteenlaitos::parse(QNetworkReply *reply)
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

        if (xml.isStartElement()){
            if(xml.name() == "Time"){
                std::string timeValue =  xml.readElementText().toStdString();
                int y = std::stoi(timeValue.substr(0,4));
                int m = std::stoi(timeValue.substr(5,2));
                int d = std::stoi(timeValue.substr(8,2));
                QDateTime dateTime;
                dateTime.setDate(QDate(y,m,d));
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
        std::pair<QDateTime,qreal> value = std::make_pair(dates[i],temps[i]);
        values.push_back(value);
    }

    //qDebug() << answer;
    reply->deleteLater();

    auto data = std::make_shared<Data>();
    return data;
}

QString API_Ilmatieteenlaitos::formURL(DataRequest)
{
    return baseURL_;
}
