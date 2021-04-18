#ifndef APICALLMANAGER_H
#define APICALLMANAGER_H

#include <QObject>
#include <memory>
#include "datarequest.h"
#include "apicaller.hh"
#include "data.hh"

/**
 * @brief The APICallManager class is used to register APICaller classes and then
 * route DataRequest objects to registered APICaller classes for processing the
 * DataRequest. The routing is made if the dataSource property of the DataRequest
 * matches the name of the registered APICaller.
 */
class APICallManager : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief APICallManager creates a new APICalleManager object
     * @param parent
     */
    explicit APICallManager(QObject *parent = nullptr);

    /**
     * @brief Register registers a new APICaller class for the APICallManager
     * to use. The apiName and createFn are stored so that the APICallManager
     * can route data requests to the APICaller which corresponds to the dataSource
     * parameter of the data request.
     * @param apiName the name which the APICaller is registered with
     * @param apiKey API Key which the APICaller might need for operation
     * @param createFn the function which creates the new API Caller object
     */
    void Register(const QString &apiName,
                  const QString &apiKey,
                  APICaller::CreateAPICallerFn createFn);

    /**
     * @brief CreateAPICaller a factory function to return a APICaller object
     * which was registered with apiName
     * @param apiName
     * @return
     */
    APICaller *CreateAPICaller(const QString &apiName);

    /**
     * @brief fetchData routes the dataRequest to the APICaller that was registered
     * with the same name as the dataRequests's dataSource
     * @param dataRequest
     */
    void fetchData(DataRequest dataRequest);
signals:

    /**
     * @brief dataFetched signals that a data was created from a parsed API response
     * @param data : the data that was created
     */
    void dataFetched(std::shared_ptr<Data> data);

    /**
     * @brief requestError signals that an error occurred during an API call
     * @param errorMessage
     */
    void requestError(QString errorMessage);

private slots:

    /**
     * @brief forwardData emits the dataFetched signal
     * @param data
     */
    void forwardData(std::shared_ptr<Data> data);

    /**
     * @brief forwardErrorMessage emits the requestError signal
     * @param errorMessage
     */
    void forwardErrorMessage(QString errorMessage);

private:

    /**
     * @brief apiCallers a register of the registered apiCallers. Stores
     * the api name and a function pointer to the APICaller's create-function
     */
    QMap<QString,APICaller::CreateAPICallerFn> apiCallers;

    /**
     * @brief apiKeys stores the api key corresponding to the registered api name
     * name
     */
    QMap<QString, QString> apiKeys;
};

#endif // APICALLMANAGER_H
