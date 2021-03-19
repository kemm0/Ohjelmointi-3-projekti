#ifndef DATA_HH
#define DATA_HH
//class used for storing the data from the api
#include <QObject>
#include <QDateTime>
#include <vector>
typedef std::vector<std::pair<QDateTime, qreal>> dataVector;
class Data : public QObject
{
    Q_OBJECT
public:
     Data(QObject *parent = nullptr);
     virtual ~Data();
    /**
     * @brief setData
     * @param id
     * @param datatype
     * @param unit
     * @param dataValues
     */
    virtual void setData(QString id, QString datatype, QString unit,dataVector dataValues);

    virtual QString getId();
    virtual QString getDatatype();
    virtual QString getUnit();
    virtual dataVector getDataValues();


private:

QString id_;
QString datatype_;
QString unit_;
dataVector dataValues_;
dataVector monthlyAvg_;
dataVector monthlyMinMaxAvg_;

};

#endif // DATA_HH
