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

protected slots:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest);

private:
    static QString baseUrl_;
};

#endif // APICALLERFINGRID_HH
