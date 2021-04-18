#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

/**
 * @brief The DataRequest struct defines parameters for an API call.
 */

struct DataRequest{

    /**
     * @brief datatype the datatype to request from an API
     */
    QString datatype;

    /**
     * @brief dataSource the api name where to get the data from
     */
    QString dataSource;

    /**
     * @brief startTime defines the starting point from which data is wanted
     */
    QDateTime startTime;

    /**
     * @brief endTime defines the ending point for the data gathering
     */
    QDateTime endTime;

    /**
     * @brief location the location from which data is wanted
     */
    QString location;

    /**
     * @brief operator QString returns the DataRequest in QString format
     */
    operator QString() const {
        return "datatype: " + datatype + ", start time: " +
                startTime.toString() + ", end time: " + endTime.toString() +
                ", location: " + location + ", data source: " + dataSource;
    }
};

#endif // DATAREQUEST_H
