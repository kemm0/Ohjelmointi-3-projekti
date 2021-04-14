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

private Q_SLOTS:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest request);

private:
    std::vector<std::pair<QDateTime,qreal>> calculateAverage(std::vector<std::pair<QDateTime,qreal>> &values);
    static const QString datetimeFormat;
    static const QMap<QString,QMap<QString,QString>> requestParameters_;
    static const QString baseURL_;
};

#endif // APICALLERFMI_H
