#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "datamanager.hh"
#include "apicallmanager.h"
#include <memory>
#include "data.hh"
#include "datarequest.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:

    /**
     * @brief dataAdded signals (the controller) that a new data was added by
     * the data manager
     * @param data : the data that was added
     */
    void dataAdded(std::shared_ptr<Data> data);

    /**
     * @brief error signals an error message
     * @param errorMessage the message
     */
    void error(QString errorMessage);

public Q_SLOTS:
    /**
     * @brief forwardData forwards created data (to controller)
     * @param data
     */
    void forwardData(std::shared_ptr<Data> data);

    /**
     * @brief removeData sends signal to dataManager to remove data
     * @param id
     */
    void removeData(QString& id);

    /**
     * @brief fetchNewData sends signal to apiCallManager to create a new request
     * @param request
     */
    void fetchNewData(DataRequest request);

    /**
     * @brief saveData signals the dataManager to save data to a file
     * @param filename
     * @param path
     * @param id
     */
    void saveData(QString filename, QString path, QString id);

    /**
     * @brief loadData signals the dataManager to load data from a file
     * @param filepath
     */
    void loadData(QString filepath);

    /**
     * @brief forwardError sends an error message signal
     * @param errorMessage
     */
    void forwardError(QString &errorMessage);

    /**
     * @brief loadPreferences signals (the dataManager?) to load preferences
     * from a file and create data objects based on the preferences
     * @param filepath : the path to the preferences file
     */
    void loadPreferences(QString filepath);

    /**
     * @brief savePreferences signals (the dataManager?) to save current
     * data objects as preferences to a (json?) file
     * @param filename
     * @param path
     */
    void savePreferences(QString filename, QString path);

private:
    std::shared_ptr<DataManager> dataManager_;
    std::shared_ptr<APICallManager> apiCallManager_;
};

#endif // BACKEND_H
