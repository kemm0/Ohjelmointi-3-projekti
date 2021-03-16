#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QObject>
#include <QDateTime>

struct DataRequest{
    QString datatype;
    QDateTime startTime;
    QDateTime endTime;
    QString location;
    bool showMonthlyAvg;
    bool showMonthlyMinMaxAvg;
};

#endif // DATAREQUEST_H
