#include "apicaller.hh"

APICaller::APICaller(QObject *parent) :
    QObject(parent),
    dataRequest_({})
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_,&QNetworkAccessManager::finished, this, &APICaller::parse);
}

void APICaller::fetchData(DataRequest dataRequest)
{
    return;
}

void APICaller::parse(QNetworkReply *reply)
{
    return;
}

void APICaller::error(QNetworkReply::NetworkError error)
{
    qDebug()<<error;
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
    reply->deleteLater();
}

QString APICaller::formURL(DataRequest dataRequest)
{
    return "";
}
