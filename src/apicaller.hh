#ifndef APICALLER_H
#define APICALLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlStreamReader>

#include "data.hh"
#include "datarequest.hh"

/**
 * @brief The APICaller class is an interface that is used to
 * create concrete APICallers
 */

class APICaller : public QObject
{
    Q_OBJECT
public:
    // function pointer to create apicaller function
    typedef APICaller* (*CreateAPICallerFn)(QString apiKey);

    /**
     * @brief APICaller creates an APICaller object
     * @param apiKey
     * @param parent
     */
    explicit APICaller(QString apiKey, QObject *parent = nullptr);

    /**
     * @brief fetchData pure virtual function that starts the
     * gathering of data from API
     * @param dataRequest
     */
    virtual void fetchData(DataRequest dataRequest) = 0;

protected Q_SLOTS:

    /**
     * @brief parse pure virtual function is used to parse the
     * retured data of the API
     * @param reply
     */
    virtual void parse(QNetworkReply *reply) = 0;

    /**
     * @brief error is used to handle network error that could occur
     * during API call
     * @param error
     */
    virtual void error(QNetworkReply::NetworkError error);

    /**
     * @brief formURL pure virtual function is used to implement forming
     * the url based on dataRequest parameters
     * @param dataRequest
     * @return
     */
    virtual QString formURL(DataRequest dataRequest) = 0;

signals:
    /**
      * @brief dataParsed forwards the data object that was created
      */
     void dataParsed(std::shared_ptr<Data>);

     /**
      * @brief requestError forwards the error message that was created during
      * the API call
      * @param errorMessage
      */
     void requestError(QString errorMessage);

protected:

     /**
      * @brief apiKey_ the api key that is used for making the API call
      */
     QString apiKey_;

     /**
      * @brief dataRequest_ the original DataRequest that was set to this APICaller object
      */
     DataRequest dataRequest_;

     /**
      * @brief manager_ handles the QNetworkReplies and QNetworkRequests that
      * are made based on the original DataRequest
      */
     QNetworkAccessManager *manager_;

     /**
      * @brief baseURL_ the base url of the API
      */
     QString baseURL_;
};

#endif // APICALLER_H
