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
    Q_PROPERTY(QString location_ READ getLocation WRITE setLocation NOTIFY locationChanged)

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();
    Q_INVOKABLE void removeChart(int chartIndex);
    Q_INVOKABLE void clearChart(int chartIndex);
    Q_INVOKABLE void setProperties(QString dataType, QString location, QString startDate, QString startTime,
                                   QString endDate, QString endTime,
                                   bool showMonthlyAvg, bool showMonthlyMinMaxAvg);

    //sets the chart from qml by accessing it via the parameter lineseries. For some reason the chart could not be accessed directly.
    Q_INVOKABLE int setChartFromSeries(int index, QtCharts::QLineSeries* series);

    //adds a chart from qml by accessing it via the parameter lineseries. For some reason the chart could not be accessed directly.
    Q_INVOKABLE int addChartFromSeries(QtCharts::QLineSeries* series);

    //add a lineSeries which visualises the given data points. Adds the lineSeries to the chart specified by chartIndex
    Q_INVOKABLE void addChartData(int chartIndex, std::vector<std::pair<QDateTime,qreal>> data);

    //set 1 or multiple lineseries to the specific chart. Previous lineseries are deleted from the chart
    Q_INVOKABLE void setChartData(int chartIndex, std::vector<std::vector<std::pair<QDateTime,qreal>>> data);

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

    QString getLocation() const;
    void setLocation(const QString &location);

private:
    QList<QtCharts::QChart*> charts;

    QDateTime startTime_;
    QDateTime endTime_;
    bool showMonthlyAvg_;
    bool showMonthlyMinMaxAvg_;
    QString dataType_;
    QString location_;
    int currentChartIndex;

signals:
    void timeChanged();
    void showMonthlyMinMaxAvgChanged();
    void showMonthlyAvgChanged();
    void dataTypeChanged();
    void currentChartIndexChanged();
    void locationChanged();
};

#endif // VIEW_HH
