#ifndef DATAMODEL_HH
#define DATAMODEL_HH

#include <QObject>
#include <memory>
#include <vector>
#include "data.hh"

class DataModel : public QObject
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);
    Data getDataByID(QString id);

    std::vector<std::shared_ptr<Data>> getAllData();

    qreal getAverage(QString id);

private:
    std::map<QString,std::shared_ptr<Data>> data;
    std::vector<std::shared_ptr<Data>> dataVector;
    std::vector<std::pair<QDateTime,qreal>> calculateMonthlyAvg(QString id);
    std::vector<std::pair<QDateTime,qreal>> calculateMonthlyMinMaxAvg(QString id);

signals:

};

#endif // DATAMODEL_HH
