#include "apicaller.hh"

APICaller::APICaller(QObject *parent) :
    QObject(parent)
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

std::shared_ptr<Data> APICaller::createDataObject(std::vector<std::pair<QDateTime, qreal> > dataVector, QString unit)
{
    auto data = std::make_shared<Data>(
                dataRequest_.datatype,
                unit,
                dataVector,
                dataRequest_.location);
    if (dataRequest_.isSplit){
        data->makeSplit();
        data->giveSplitId(dataRequest_.splitId);
    }
    return data;
}

QString APICaller::formURL(DataRequest dataRequest)
{
    return "";
}
