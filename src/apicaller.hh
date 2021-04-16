#ifndef APICALLER_H
#define APICALLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlStreamReader>

#include "data.hh"
#include "datarequest.h"

class APICaller : public QObject
{
    Q_OBJECT
public:
    explicit APICaller(QObject *parent = nullptr);
    virtual void fetchData(DataRequest dataRequest) = 0;

protected Q_SLOTS:
    virtual void parse(QNetworkReply *reply) = 0;
    virtual void error(QNetworkReply::NetworkError error);
    virtual QString formURL(DataRequest dataRequest) = 0;

signals:
     void dataParsed(std::shared_ptr<Data>);
     void requestError(QString errorMessage);

protected:
    std::shared_ptr<Data> createDataObject(std::vector<std::pair<QDateTime,qreal>> dataVector, QString unit);
    QNetworkAccessManager *manager_;
    DataRequest dataRequest_;
    QString baseURL_;
};

#endif // APICALLER_H
