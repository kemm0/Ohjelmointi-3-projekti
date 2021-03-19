#ifndef API_ILMATIETEENLAITOS_HH
#define API_ILMATIETEENLAITOS_HH

#include "api.hh"

class API_Ilmatieteenlaitos : public API
{
    Q_OBJECT
public:
    explicit API_Ilmatieteenlaitos(QObject *parent = nullptr);

private Q_SLOTS:
    void parse(QNetworkReply *reply);
    QString formURL(DataRequest);
};

#endif // API_ILMATIETEENLAITOS_HH
