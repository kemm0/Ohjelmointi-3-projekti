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
    explicit Data(QObject *parent = nullptr);

    /**
     * @brief setData
     * @param id
     * @param datatype
     * @param unit
     * @param dataValues
     * @param monthlyAvg
     * @param monthlyMinMaxAvg
     */
    void setData(QString id, QString datatype, QString unit,dataVector dataValues);
private:
QString id_;
QString datatype_;
QString unit_;
dataVector dataValues_;
dataVector monthlyAvg_;
dataVector monthlyMinMaxAvg_;
};

#endif // DATA_HH
