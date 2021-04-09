#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

struct DataRequest{
    QString datatype;
    QDateTime startTime;
    QDateTime endTime;
    QString location;
    operator QString() const {
        return "datatype: " + datatype + ", start time: " + startTime.toString() +
                ", end time: " + endTime.toString() + ", location: " + location;
    }
};

#endif // DATAREQUEST_H
