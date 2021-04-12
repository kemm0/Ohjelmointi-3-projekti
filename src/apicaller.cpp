#include "apicaller.hh"

APICaller::APICaller(QObject *parent) :
    QObject(parent)
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_,&QNetworkAccessManager::finished, this, &APICaller::parse);
}

void APICaller::error(QNetworkReply::NetworkError error)
{
    qDebug()<<error;
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
    reply->deleteLater();
}
