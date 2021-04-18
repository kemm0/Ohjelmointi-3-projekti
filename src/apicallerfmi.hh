#ifndef APICALLERFMI_H
#define APICALLERFMI_H

#include "apicaller.hh"

/**
 * @brief The APICallerFMI class is used to get data from the FMI open dataset API
 */
class APICallerFMI : public APICaller
{
    Q_OBJECT
public:

    /**
     * @brief APICallerFMI creates a new APICallerFMI object
     * @param apiKey
     * @param parent
     */
    explicit APICallerFMI(QString apiKey, QObject *parent = nullptr);

    /**
     * @brief fetchData creates a QNetworkRequest to request data from the FMI API
     * @param dataRequest
     */
    void fetchData(DataRequest dataRequest);

    /**
     * @brief dataTypes returns the datatypes that APICallerFMI handles
     * @return
     */
    static QList<QString> dataTypes();

    /**
     * @brief Create creates a new APICallerFMI object
     * @param apiKey
     * @return
     */
    static APICaller *Create(QString apiKey);

private Q_SLOTS:

    /**
     * @brief parses data from the API reply and creates a data object based on it
     * @param reply
     */
    void parse(QNetworkReply *reply);

    /**
     * @brief formURL forms the API call url based on parameters in request
     * @param request
     * @return
     */
    QString formURL(DataRequest request);

private:

    bool requestSplit;

    /**
     * @brief splitRequests_ holds DataRequests that were split from the
     * original DataRequest. Used when the time range for the API call is too
     * big.
     */
    QMap<int,DataRequest> splitRequests_;
    QVector<QNetworkReply*> replies;

    /**
     * @brief dataVector data values that are parsed from the API response
     */
    std::vector<std::pair<QDateTime,qreal>> dataVector;
    static const QString datetimeFormat;

    /**
     * @brief requestParameters_ static parameters that are used for forming the
     * API call url
     */
    static const QMap<QString,QMap<QString,QString>> requestParameters_;
    static const QString baseURL_;

    bool requestFailed;

    /**
     * @brief splitDataRequest splits the request into multiple requests based
     * on the maximum request time range (hours) defined in requestParameters
     * @param request the original data request
     * @param splitFactor defines how many requests the original request is
     * split into
     * @return
     */
    QMap<int,DataRequest> splitDataRequest(DataRequest& request,
                                           int &splitFactor);

    /**
     * @brief calculateAverage calculates averages value of a time period
     * @param values
     * @return a std vector of pairs with the first value being a the start time
     * of the data request and the average value of the calculation. The last
     * value is the end time of the data request and the average value of the
     * calculation
     */
    std::vector<std::pair<QDateTime,qreal>> calculateAverage(
            std::vector<std::pair<QDateTime,qreal>> &values);
};

#endif // APICALLERFMI_H
