#ifndef API_HH
#define API_HH

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlStreamReader>

#include "data.hh"
#include "DataRequest.h"

class API : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = nullptr);
    std::shared_ptr<Data> fetchData(DataRequest dataRequest);

private Q_SLOTS:
    virtual std::shared_ptr<Data> parse(QNetworkReply *reply) = 0;
    void error(QNetworkReply::NetworkError error);

private:
    virtual QString formURL(DataRequest) = 0;

    QNetworkAccessManager *manager_;
    QString baseURL_;
};

#endif // API_HH
