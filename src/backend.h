#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "datamanager.hh"
#include "apicallmanager.h"
#include <memory>
#include "data.hh"
#include "datarequest.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    std::map<QString, std::vector<std::shared_ptr<Data>>> getExistingData(QString id);
    std::vector<std::shared_ptr<Data>> loadData(QString filepath);
    std::vector<std::shared_ptr<Data>> loadPreferences(QString filepath);

signals:
    void test(Data* data);
    void dataAdded(std::shared_ptr<Data> data);

public Q_SLOTS:
    void forwardData(std::shared_ptr<Data> data);
    void removeData(QString& id);
    void fetchNewData(DataRequest request);

private:
    std::shared_ptr<DataManager> dataManager_;
    std::shared_ptr<APICallManager> apiCallManager_;
};

#endif // BACKEND_H
