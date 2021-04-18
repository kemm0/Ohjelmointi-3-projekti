#include "apicaller.hh"

APICaller::APICaller(QString apiKey,QObject *parent) :
    QObject(parent),
    apiKey_(apiKey),
    dataRequest_({})
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_,&QNetworkAccessManager::finished, this, &APICaller::parse);
}

void APICaller::error(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    emit requestError("An error happened during the API request. Here's the full "
    "error message: \n" + reply->readAll());
    reply->deleteLater();
}

