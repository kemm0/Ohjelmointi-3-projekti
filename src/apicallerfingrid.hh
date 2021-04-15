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
    const QString apiKey_;
    static const QString baseUrl_;
    static const QString datetimeFormat_;
    static const QString responseDatetimeFormat_;
    static const QMap<QString,QMap<QString,QString>> dataRequestParameters;
};

#endif // APICALLERFINGRID_HH
