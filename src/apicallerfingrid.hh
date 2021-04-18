#ifndef APICALLERFINGRID_HH
#define APICALLERFINGRID_HH

#include <QObject>
#include "apicaller.hh"

/**
 * @brief The APICallerFingrid class is used to get data from Fingrid API
 */

class APICallerFingrid : public APICaller
{
    Q_OBJECT
public:

    /**
     * @brief APICallerFingrid creates a APICallerFingrid object
     * @param apiKey
     * @param parent
     */
    explicit APICallerFingrid(QString apiKey, QObject *parent = nullptr);

    /**
     * @brief fetchData creates a QNetworkRequest to request data from the Fingrid API
     * @param dataRequest
     */
    void fetchData(DataRequest dataRequest);

    /**
     * @brief dataTypes
     * @return QList of the datatypes that the Fingrid API handles
     */
    static QList<QString> dataTypes();

    /**
     * @brief Create creates a new APICallerFingrid object
     * @param apiKey
     * @return
     */
    static APICaller * Create(QString apiKey);

public slots:

    /**
     * @brief parse parses data from the API reply and creates a data object based on it
     * @param reply
     */
    void parse(QNetworkReply *reply);

    /**
     * @brief formURL forms the API call url based on parameters in dataRequest
     * @param dataRequest
     * @return
     */
    QString formURL(DataRequest dataRequest);

private:
    static const QString baseUrl_;

    static const QString datetimeFormat_;

    static const QString responseDatetimeFormat_;

    /**
     * @brief requestParameters_ static parameters that are used for forming the
     * API call url
     */
    static const QMap<QString,QMap<QString,QString>> requestParameters_;

    /**
     * @brief splitRequests_ holds DataRequests that are split from the original
     * DataRequest. Used to make multiple API calls for the same datatype.
     */
    QMap<int,DataRequest> splitRequests_;

    /**
     * @brief dataVectors_ data values for each split DataRequest
     */
    QMap<int,std::vector<std::pair<QDateTime,qreal>>> dataVectors_;

    QVector<QNetworkReply*> replies;

    bool requestSplit;
    int requestCounter;
    bool requestFailed;

    /**
     * @brief calculatePercentages calculates percentages between nuclear, wind
     * and hydro power productions
     */
    void calculatePercentages();

    /**
     * @brief createNetworkRequest creates a network request based on data request parameters
     * @param request
     */
    void createNetworkRequest(DataRequest &request);
};

#endif // APICALLERFINGRID_HH
