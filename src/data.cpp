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



    QNetworkReply *reply = manager_->get(req);

    connect(reply, &QNetworkReply::errorOccurred, this, &Data::error);

}

void Data::downloadCompleted(QNetworkReply *reply)
{
    //after the download, reade the data
    qDebug() << reply->readAll();
}

void Data::error(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
}
