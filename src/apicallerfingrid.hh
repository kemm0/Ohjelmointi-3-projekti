#ifndef APICALLERFINGRID_HH
#define APICALLERFINGRID_HH

#include <QObject>
#include "apicaller.hh"

class APICallerFingrid : public APICaller
{
    Q_OBJECT
public:
    explicit APICallerFingrid(QObject *parent = nullptr);

signals:


    // APICaller interface
public:
    void fetchData(DataRequest dataRequest);
    static QVector<QString> dataTypes();

protected slots:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest dataRequest);

private:
    static const QString API_KEY;
    static const QString baseUrl_;
    static const QVector<QString> datatypes_;
    static const QString datetimeFormat_;
    static const QString responseDatetimeFormat_;
    QMap<QString,QMap<QString,QString>> dataTypeParameters;
};

#endif // APICALLERFINGRID_HH
