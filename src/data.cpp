#include "data.hh"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtDebug>

Data::Data(QObject *parent):
    QObject(parent)
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_,&QNetworkAccessManager::finished, this, &Data::downloadCompleted);
}

void Data::fetchdDataFMI()
{

}

void Data::fetchDataFinGrid(const QString &url)
{

    QNetworkRequest req = QNetworkRequest(url);

    //used to set the api key for requests
    req.setRawHeader(QByteArray("x-api-key"),QByteArray("TVJel2EJEE3txr1XXtVt57X3H1Kyspyd3pHLvw4X"));

    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &Data::error);

}

void Data::downloadCompleted(QNetworkReply *reply)
{
    //after the download, read the data
    qDebug() << reply->readAll();
    reply->deleteLater();
}

void Data::error(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
    reply->deleteLater();
}
