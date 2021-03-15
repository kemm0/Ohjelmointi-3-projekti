#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QObject>
#include <QDateTime>
#include "Datatypes.h"

struct dataRequest{
    QString id;
    Datatype datatype;
    QDateTime startTime;
    QDateTime endTime;
    QString location;
    bool showMonthlyAvg;
    bool showMonthlyMinMaxAvg;
};

#endif // DATAREQUEST_H
