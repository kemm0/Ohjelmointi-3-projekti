#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <memory>
#include <vector>
#include "data.hh"

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

public slots:

    /**
     * @brief addData stores the given data object in data_ map
     * @param data
     */
    void addData(std::shared_ptr<Data> data);

    /**
     * @brief saveDataToFile saves data object to a json file
     * @param filename : name of the file (without file extension)
     * @param path : path to the folder where to store the file
     * @param id : id of the data to be saved
     */
    void saveDataToFile(QString filename, QString path, QString id);

    /**
     * @brief loadDataFromFile loads and creates a data object from json file
     * @param filepath : path of the file where to store the file
     */
    void loadDataFromFile(QString filepath);

    /**
     * @brief removeData removes data object from the data_ map
     * @param id : id of the data to be removed
     */
    void removeData(QString& id);

signals:
    void dataAdded(std::shared_ptr<Data> data);

private:
    std::map<QString,std::shared_ptr<Data>> data_;

};

#endif // DATAMANAGER_H
