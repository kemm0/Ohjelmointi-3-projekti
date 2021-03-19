#ifndef API_CALLER_H
#define API_CALLER_H

#include <QObject>
#include <memory>
#include "DataRequest.h"
#include "api.hh"
#include "api_ilmatieteenlaitos.hh"

class API_caller : public QObject
{
    Q_OBJECT
public:
    explicit API_caller(QObject *parent = nullptr);
    void fetchData(DataRequest dataRequest);
    std::map<QString, std::shared_ptr<API>> getAPIs();

private:
    std::map<QString, std::shared_ptr<API>> APIs_;

signals:

};

#endif // API_CALLER_H
