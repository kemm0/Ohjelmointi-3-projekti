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
    void fetchData(DataRequest dataRequest);

private Q_SLOTS:
    virtual void parse(QNetworkReply *reply) = 0;
    void error(QNetworkReply::NetworkError error);

signals:
     void dataParsed(std::shared_ptr<Data>);

protected:
    virtual QString formURL(DataRequest) = 0;

    std::shared_ptr<Data> requestedData_;
    QString baseURL_;

private:
    QNetworkAccessManager *manager_;
};

#endif // API_HH
