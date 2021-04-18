#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "datamanager.hh"
#include "apicallmanager.h"
#include <memory>
#include "data.hh"
#include "datarequest.h"
#include "apicallerfmi.hh"
#include "apicallerfingrid.hh"

/**
 * @brief The Backend class holds the backend application logic. It is used to
 * handle the different signals coming from the GUI.
 */

class Backend : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Backend creates a new Backend object and sets connections to
     * APICallManager and DataManager.
     * @param apiConfigPath path to the apiconfig file
     * @param parent
     */
    explicit Backend(QString apiConfigPath, QObject *parent = nullptr);

signals:

    /**
     * @brief dataAdded signals that a new data was added by
     * the data manager
     * @param data : the data that was added
     */
    void dataAdded(QVariant data);

    /**
     * @brief error signals an error message
     * @param errorMessage the message
     */
    void error(QVariant errorMessage);

public Q_SLOTS:

    /**
     * @brief removeData calls the dataManager to remove a data
     * @param id the id of the data object
     */
    void removeData(QVariant id);

    /**
     * @brief fetchNewData calls the apiCallManager to create a new API request
     * @param request a data request in QVariant form
     */
    void fetchNewData(QVariant properties);

    /**
     * @brief saveData calls the dataManager to save data to a file
     * @param filename
     * @param path
     * @param id
     */
    void saveData(QVariant filename, QVariant path, QVariant id);

    /**
     * @brief loadData calls the dataManager to load data from a file
     * @param filepath
     */
    void loadData(QVariant filePath);

    /**
     * @brief loadPreferences signals calls the dataManager to load preferences
     * from a file and creates data objects based on the preferences
     * @param filepath : the path to the preferences file
     */
    void loadPreferences(QVariant filepath);

    /**
     * @brief savePreferences calls the dataManager to save current
     * data objects as preferences to a file
     * @param filename
     * @param path
     */
    void savePreferences(QVariant filename, QVariant filepath);

    /**
     * @brief requestPrefData creates DataRequest objects based on the
     * preferences from DataManager and calls the APICallManager to create
     * API calls with the DataRequest objects
     * @param pref
     */
    void requestPrefData(QJsonObject pref);

private Q_SLOTS:

    /**
     * @brief forwardData forwards the data that was added to dataManager
     * @param data the data from dataManager
     */
    void forwardData(std::shared_ptr<Data> data);

    /**
     * @brief sendError signals an error message
     * @param errorMessage
     */
    void sendError(QString errorMessage);

private:
    std::shared_ptr<DataManager> dataManager_;
    std::shared_ptr<APICallManager> apiCallManager_;

    /**
     * @brief apiConfig_ holds the api keys for different APIs
     */
    QMap<QString,QString> apiConfig_;

    /**
     * @brief loadAPIConfig loads the API keys from the apiConfig file.
     * The file format must be APINAME=KEY. The api keys are then passed to
     * the APICallManager.
     * @param path to the APIConfig file
     */
    void loadAPIConfig(QString path);
};

#endif // BACKEND_H
