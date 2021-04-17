#ifndef APICALLERFINGRID_HH
#define APICALLERFINGRID_HH

#include <QObject>
#include "apicaller.hh"

class APICallerFingrid : public APICaller
{
    Q_OBJECT
public:
    explicit APICallerFingrid(QString apiKey, QObject *parent = nullptr);

signals:

public:
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

    static APICaller * Create(QString apiKey) { return new APICallerFingrid(apiKey); }

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
    static const QMap<QString,QMap<QString,QString>> requestParameters_;
    QMap<int,DataRequest> splitRequests_;
    QMap<int,std::vector<std::pair<QDateTime,qreal>>> dataVectors_;
    void calculatePercentages();
    void createNetworkRequest(DataRequest &request);
    QVector<QNetworkReply*> replies;
    bool requestSplit;
    int requestCounter;
};

#endif // APICALLERFINGRID_HH
