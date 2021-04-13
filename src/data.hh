#ifndef DATA_HH
#define DATA_HH
//class used for storing the data from the api
#include <QObject>
#include <QDateTime>
#include <vector>
#include <QJsonObject>

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

    static Data* fromJSON(QJsonObject& document);
    QJsonObject toJSON();

    void setDatatype(QString &datatype);
    void setUnit(QString &unit);
    void setLocation(QString &location);
    void addDataValues(dataVector &dataValues);
    void setDataValues(dataVector &dataValues);

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
