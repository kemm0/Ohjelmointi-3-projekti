#ifndef APICALLMANAGER_H
#define APICALLMANAGER_H

#include <QObject>
#include <memory>
#include "datarequest.h"
#include "apicaller.hh"
#include "apicallerfmi.hh"

class APICallManager : public QObject
{
    Q_OBJECT
public:
    explicit APICallManager(QObject *parent = nullptr);
    void fetchData(DataRequest dataRequest);
signals:
    void dataFetched(std::shared_ptr<Data> data);

private slots:
    void forwardData(std::shared_ptr<Data> data);

};

#endif // APICALLMANAGER_H
