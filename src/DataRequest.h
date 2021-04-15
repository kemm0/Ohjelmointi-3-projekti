#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

struct DataRequest{
    QString datatype;
    QString dataSource;
    QDateTime startTime;
    QDateTime endTime;
    QString location;
    operator QString() const {
        return "datatype: " + datatype + ", start time: " + startTime.toString() +
                ", end time: " + endTime.toString() + ", location: " + location
                + ", data source: " + dataSource;
    }
};

#endif // DATAREQUEST_H
