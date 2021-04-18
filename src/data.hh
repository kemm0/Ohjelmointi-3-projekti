#ifndef DATA_HH
#define DATA_HH
//class used for storing the data from the api
#include <QObject>
#include <QDateTime>
#include <vector>
#include <QJsonObject>
#include <QtCharts>

using namespace QtCharts;
typedef std::vector<std::pair<QDateTime, qreal>> dataVector;
/**
 * @brief The Data class
 */
class Data : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Data
     * @param datatype
     * @param unit
     * @param location
     * @param dataSource
     * @param parent
     */
    Data(QString datatype, QString unit,
          QString location, QString dataSource, QObject *parent = nullptr);

    /**
     * @brief Data creates a new Data object
     * @param parent
     */
    Data(QObject *parent = nullptr);

    ~Data();

    /**
     * @brief getId
     * @return the ID of the data
     */
    QString getId();

    /**
     * @brief getDatatype
     * @return the data type of the data
     */
    QString getDatatype();

    /**
     * @brief getUnit
     * @return the unit of the data
     */
    QString getUnit();

    /**
     * @brief getLocation
     * @return the location of the data
     */
    QString getLocation();

    /**
     * @brief getDataValues
     * @return the data values of the data object
     */
    dataVector getDataValues();

    /**
     * @brief fromJSON creates a data object from a QjsonObject
     * @param jsonObject from which the data object is created
     * @return the created data object
     */
    static Data* fromJSON(QJsonObject& jsonObject);

    /**
     * @brief toJSON creates a QJsonobject from a data object
     * @return the created QJsonObject
     */
    QJsonObject toJSON();

    /**
     * @brief setDatatype sets the datatype of the data
     * @param datatype
     */
    void setDatatype(QString &datatype);

    /**
     * @brief setUnit sets the unit of the data
     * @param unit
     */
    void setUnit(QString &unit);

    /**
     * @brief setLocation sets the location of the data
     * @param location
     */
    void setLocation(QString &location);

    /**
     * @brief addDataValues appends new data values to the data's data values
     * @param dataValues
     */
    void addDataValues(dataVector &dataValues);

    /**
     * @brief setDataValues sets the data values to the data object
     * @param dataValues
     */
    void setDataValues(dataVector &dataValues);

    /**
     * @brief print prints the member variable values of the data object
     */
    void print();

    /**
     * @brief getDataSource
     * @return the source API of the data
     */
    QString getDataSource() const;

    /**
     * @brief setDataSource sets the source API of the data
     * @param dataSource
     */
    void setDataSource(const QString &dataSource);

    /**
     * @brief jsonDateTimeFormat the time format that is used when storing
     * date values in json format
     */
    static const QString jsonDateTimeFormat;

private:
    /**
     * @brief idCounter generates the ID for the data object
     */
    static int idCounter;
    QString dataSource_;
    QString id_;
    QString datatype_;
    QString unit_;
    QString location_;
    dataVector dataValues_;
};

#endif // DATA_HH
