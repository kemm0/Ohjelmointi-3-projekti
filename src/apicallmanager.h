#ifndef APICALLMANAGER_H
#define APICALLMANAGER_H

#include <QObject>
#include <memory>
#include "datarequest.h"
#include "data.hh"

class APICallManager : public QObject
{
    Q_OBJECT
public:
    explicit APICallManager(QObject *parent = nullptr);

    /**
     * @brief fetchData routes the dataRequest to the APICaller that handles the
     * dataRequest's datatype
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
    void loadAPIConfig();
    QMap<QString,QString> apiConfig;
};

#endif // APICALLMANAGER_H
