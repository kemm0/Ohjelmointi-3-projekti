#ifndef APICALLERFMI_H
#define APICALLERFMI_H

#include "apicaller.hh"

class APICallerFMI : public APICaller
{
    Q_OBJECT
public:
    explicit APICallerFMI(QObject *parent = nullptr);
    void fetchData(DataRequest dataRequest);
    static QList<QString> dataTypes();
    static APICaller * Create() { return new APICallerFMI(); }

private Q_SLOTS:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest request);

private:

    bool requestSplit;
    QMap<int,DataRequest> splitRequests_;
    QVector<QNetworkReply*> replies;

    std::vector<std::pair<QDateTime,qreal>> dataVector;
    static const QString datetimeFormat;
    static const QMap<QString,QMap<QString,QString>> requestParameters_;
    static const QString baseURL_;

    QMap<int,DataRequest> splitDataRequest(DataRequest& request, int &splitFactor);
    std::vector<std::pair<QDateTime,qreal>> calculateAverage(std::vector<std::pair<QDateTime,qreal>> &values);
};

#endif // APICALLERFMI_H
