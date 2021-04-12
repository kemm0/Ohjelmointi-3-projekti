#ifndef APICALLERFMI_H
#define APICALLERFMI_H

#include "apicaller.hh"

class APICallerFMI : public APICaller
{
    Q_OBJECT
public:
    explicit APICallerFMI(QObject *parent = nullptr);
    void fetchData(DataRequest dataRequest);

private Q_SLOTS:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest request);

private:
    static const QVector<QString> datatypes;
    static const QString datetimeFormat;
    QMap<QString,QMap<QString,QString>> dataTypeParameters;
};

#endif // APICALLERFMI_H
