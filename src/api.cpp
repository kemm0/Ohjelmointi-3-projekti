#include "api.hh"

API::API(QObject *parent) : QObject(parent)
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_,&QNetworkAccessManager::finished, this, &API::parse);
}

std::shared_ptr<Data> API::fetchData(DataRequest dataRequest)
{
    QNetworkRequest req = QNetworkRequest(formURL(dataRequest));

    //used to set the api key for requests
    //req.setRawHeader(QByteArray("x-api-key"),QByteArray(""));

    QNetworkReply *reply = manager_->get(req);

    //connect to error slot if error signaled
    connect(reply, &QNetworkReply::errorOccurred, this, &API::error);

    return nullptr;
}

void API::error(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
    reply->deleteLater();
}
