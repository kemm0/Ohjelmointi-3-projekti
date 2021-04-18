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

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QString apiConfigPath, QObject *parent = nullptr);

signals:

    /**
     * @brief dataAdded signals (the controller) that a new data was added by
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
     * @brief removeData sends signal to dataManager to remove data
     * @param id
     */
    void removeData(QVariant id);

    /**
     * @brief fetchNewData sends signal to apiCallManager to create a new request
     * @param request
     */
    void fetchNewData(QVariant properties);

    /**
     * @brief saveData signals the dataManager to save data to a file
     * @param filename
     * @param path
     * @param id
     */
    void saveData(QVariant filename, QVariant path, QVariant id);

    /**
     * @brief loadData signals the dataManager to load data from a file
     * @param filepath
     */
    void loadData(QVariant filePath);

    /**
     * @brief loadPreferences signals (the dataManager?) to load preferences
     * from a file and create data objects based on the preferences
     * @param filepath : the path to the preferences file
     */
    void loadPreferences(QVariant filepath);

    /**
     * @brief savePreferences signals (the dataManager?) to save current
     * data objects as preferences to a (json?) file
     * @param filename
     * @param path
     */
    void savePreferences(QVariant filename, QVariant filepath);

    /**
     * @brief forwardData forwards the data that was added to dataManager
     * @param data the data from dataManager
     */

    void requestPrefData(QJsonObject pref);
private Q_SLOTS:
    void forwardData(std::shared_ptr<Data> data);

    void sendError(QString errorMessage);

private:
    std::shared_ptr<DataManager> dataManager_;
    std::shared_ptr<APICallManager> apiCallManager_;
    QMap<QString,QString> apiConfig_;

    void loadAPIConfig(QString path);
};

#endif // BACKEND_H
