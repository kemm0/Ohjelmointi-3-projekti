#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QLineSeries>
#include <QChart>
#include <QDateTime>
#include <QStringList>
#include "data.hh"
#include <QtQuick>
#include <QStringListModel>

class View : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString startDateValue READ getStartDateValue NOTIFY timeChanged)
    Q_PROPERTY(QString startTimeValue READ getStartTimeValue NOTIFY timeChanged)
    Q_PROPERTY(QString endDateValue READ getEndDateValue NOTIFY timeChanged)
    Q_PROPERTY(QString endTimeValue READ getEndTimeValue NOTIFY timeChanged)
    Q_PROPERTY(bool showMonthlyAvg_ READ getShowMonthlyAvg NOTIFY showMonthlyAvgChanged)
    Q_PROPERTY(bool showMonthlyMinMaxAvg_ READ getShowMonthlyMinMaxAvg NOTIFY showMonthlyMinMaxAvgChanged)
    Q_PROPERTY(QString dataType_ READ getDataType NOTIFY dataTypeChanged)
    Q_PROPERTY(int currentChartIndex READ getCurrentChartIndex WRITE setCurrentChartIndex NOTIFY currentChartIndexChanged)

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();
    Q_INVOKABLE void removeChart(int index);
    Q_INVOKABLE void clearChart(int index);
    Q_INVOKABLE void setProperties(QString dataType, QString startDate, QString startTime,
                                   QString endDate, QString endTime,
                                   bool showMonthlyAvg, bool showMonthlyMinMaxAvg);
    Q_INVOKABLE int setChartFromSeries(int index, QtCharts::QLineSeries* series); //tallentaa qml:stä napatun lineserieksen chartin. Palauttaa indeksin charts-listassa
    Q_INVOKABLE int addChartFromSeries(QtCharts::QLineSeries* series);
    Q_INVOKABLE void addChartData(int chartIndex, std::vector<std::pair<QDateTime,qreal>> data);

    QString getStartDateValue();
    QString getStartTimeValue();
    QString getEndDateValue();
    QString getEndTimeValue();
    bool getShowMonthlyAvg();
    bool getShowMonthlyMinMaxAvg();
    QString getDataType();
    QDateTime getStartTime();
    QDateTime getEndTime();

    int getCurrentChartIndex() const;
    void setCurrentChartIndex(int value);

private:
    QList<QtCharts::QChart*> charts;

    QDateTime startTime_;
    QDateTime endTime_;
    bool showMonthlyAvg_;
    bool showMonthlyMinMaxAvg_;
    QString dataType_;
    int currentChartIndex;

signals:
    void timeChanged();
    void showMonthlyMinMaxAvgChanged();
    void showMonthlyAvgChanged();
    void dataTypeChanged();
    void currentChartIndexChanged();
};

#endif // VIEW_HH
