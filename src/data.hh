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
class Data : public QObject
{
    Q_OBJECT
public:
     Data(QString datatype, QString unit, dataVector dataValues, QString location, QObject *parent = nullptr);
     Data(QObject *parent = nullptr);
     ~Data();
    QString getId();
    QString getDatatype();
    QString getUnit();
    QString getLocation();
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

    void setDatatype(QString &datatype);
    void setUnit(QString &unit);
    void setLocation(QString &location);
    void addDataValues(dataVector &dataValues);
    void setDataValues(dataVector &dataValues);

    /**
     * @brief print prints the member variable values of the data object
     */
    void print();

private:
    static int idCounter;
    QString id_;
    QString datatype_;
    QString unit_;
    QString location_;
    dataVector dataValues_;

    static const QString jsonDateTimeFormat;
};

#endif // DATA_HH
