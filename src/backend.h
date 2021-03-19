#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "datamodel.hh"
#include "api_caller.h"
#include <memory>
#include "data.hh"
#include "DataRequest.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    std::map<QString, std::vector<std::shared_ptr<Data>>> getExistingData(QString id);
    void fetchNewData(DataRequest request);
    std::vector<std::shared_ptr<Data>> loadData(QString filepath);
    std::vector<std::shared_ptr<Data>> loadPreferences(QString filepath);

private Q_SLOTS:
    void requestParsed(std::shared_ptr<Data> data);

signals:
    void requestComplete(std::vector<std::pair<QDateTime,qreal>>);

private:
    std::shared_ptr<DataModel> dataModel_;
    std::shared_ptr<API_caller> apiCaller_;

signals:

};

#endif // BACKEND_H
