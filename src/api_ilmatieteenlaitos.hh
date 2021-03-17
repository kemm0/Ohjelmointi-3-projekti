#ifndef API_ILMATIETEENLAITOS_HH
#define API_ILMATIETEENLAITOS_HH

#include "api.hh"

class API_Ilmatieteenlaitos : public API
{
    Q_OBJECT
public:
    explicit API_Ilmatieteenlaitos(QObject *parent = nullptr);

private Q_SLOTS:
    std::shared_ptr<Data> parse(QNetworkReply *reply);

private:
    QString formURL(DataRequest);

    QString baseURL_;
};

#endif // API_ILMATIETEENLAITOS_HH
