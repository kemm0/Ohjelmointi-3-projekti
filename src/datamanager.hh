#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <memory>
#include <vector>
#include "data.hh"

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    Data getDataByID(QString id);

    std::vector<std::shared_ptr<Data>> getAllData();

    qreal getAverage(QString id);
public slots:
    void addData(std::shared_ptr<Data> data);
    void saveDataToFile(QString filename, QString path, QString id);
    void removeData(QString& id);

private:
    std::map<QString,std::shared_ptr<Data>> data_;

signals:
    void dataAdded(std::shared_ptr<Data> data);

};

#endif // DATAMANAGER_H
