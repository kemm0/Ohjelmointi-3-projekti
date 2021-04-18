#ifndef APICALLER_H
#define APICALLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlStreamReader>

#include "data.hh"
#include "DataRequest.h"

class APICaller : public QObject
{
    Q_OBJECT
public:
    typedef APICaller* (*CreateAPICallerFn)(QString apiKey);
    explicit APICaller(QString apiKey, QObject *parent = nullptr);
    virtual void fetchData(DataRequest dataRequest) = 0;

protected Q_SLOTS:
    virtual void parse(QNetworkReply *reply) = 0;
    virtual void error(QNetworkReply::NetworkError error);
    virtual QString formURL(DataRequest dataRequest) = 0;

signals:
     void dataParsed(std::shared_ptr<Data>);
     void requestError(QString errorMessage);

protected:
    QString apiKey_;
    DataRequest dataRequest_;
    QNetworkAccessManager *manager_;
    QString baseURL_;
};

#endif // APICALLER_H
