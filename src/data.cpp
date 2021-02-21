#include "data.hh"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtDebug>
#include <QXmlStreamReader>

Data::Data(QObject *parent):
    QObject(parent)
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_,&QNetworkAccessManager::finished, this, &Data::downloadCompleted);
}

void Data::fetchdDataFMI()
{

}

void Data::fetchData(const QString &url)
{

    QNetworkRequest req = QNetworkRequest(url);

    //used to set the api key for requests
    //req.setRawHeader(QByteArray("x-api-key"),QByteArray(""));

    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &Data::error);

}

void Data::downloadCompleted(QNetworkReply *reply)
{

    QXmlStreamReader xml;
    QByteArray answer = reply->readAll();
    xml.addData(answer);
    //after the download, read the data




    while (!xml.atEnd()){
        xml.readNext();

        if (xml.isStartElement()){
            if(xml.name() == "Time"){
                QString time = xml.readElementText();
                qDebug() << time;
                dates.push_back(time);
            }

            else if (xml.name() == "ParameterValue"){
                QString value = xml.readElementText();
                double temp = value.toDouble();
                qDebug() << temp;
                temps.push_back(temp);
            }
        }


    }
    if (xml.hasError()){
        qDebug() << "XML error: " << xml.errorString().data();
    }
    //qDebug() << answer;
    reply->deleteLater();
}

void Data::error(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
    reply->deleteLater();
}
