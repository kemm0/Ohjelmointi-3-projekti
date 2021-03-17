#ifndef API_CALLER_H
#define API_CALLER_H

#include <QObject>
#include <memory>
#include "DataRequest.h"
#include "api.hh"

class API_caller : public QObject
{
    Q_OBJECT
public:
    explicit API_caller(QObject *parent = nullptr);
    std::shared_ptr<Data> fetchData(DataRequest dataRequest);

private:
    std::map<QString, std::shared_ptr<API>> APIs_;

signals:

};

#endif // API_CALLER_H
