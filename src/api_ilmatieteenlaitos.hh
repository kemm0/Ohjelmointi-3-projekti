#ifndef API_ILMATIETEENLAITOS_HH
#define API_ILMATIETEENLAITOS_HH

#include "api.hh"

class API_Ilmatieteenlaitos : public API
{
    Q_OBJECT
public:
    explicit API_Ilmatieteenlaitos(QObject *parent = nullptr);
    static const QString datetimeFormat;

private Q_SLOTS:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest request);
private:
    static const QVector<QString> locations;
};

#endif // API_ILMATIETEENLAITOS_HH
