#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QLineSeries>
#include <QChart>
#include <QDateTime>
#include "data.hh"
#include <QtQuick>

class View : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString startDateValue READ getStartDateValue NOTIFY timeChanged)
    Q_PROPERTY(QString startTimeValue READ getStartTimeValue NOTIFY timeChanged)
    Q_PROPERTY(QString endDateValue READ getEndDateValue NOTIFY timeChanged)
    Q_PROPERTY(QString endTimeValue READ getEndTimeValue NOTIFY timeChanged)
    Q_PROPERTY(bool showMonthlyAvg_ READ getShowMonthlyAvg NOTIFY showMonthlyAvgChanged)
    Q_PROPERTY(bool showMonthlyMinMaxAvg_ READ getShowMonthlyMinMaxAvg NOTIFY showMonthlyMinMaxAvgChanged)

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();

    Q_INVOKABLE void setChartData(QString chart_id,std::vector<std::shared_ptr<Data>> data);
    Q_INVOKABLE void removeChart(QString chart_id);
    Q_INVOKABLE void addChart(std::vector<std::shared_ptr<Data>> data);
    Q_INVOKABLE void changeGridSize(int size);
    Q_INVOKABLE void setProperties(QString startDate, QString startTime,
                                   QString endDate, QString endTime,
                                   bool showMonthlyAvg, bool showMonthlyMinMaxAvg);

private:
    std::map<QString,std::vector<QtCharts::QLineSeries*>> chartData;
    QDateTime startTime_;
    QDateTime endTime_;
    bool showMonthlyAvg_;
    bool showMonthlyMinMaxAvg_;

    QString getStartDateValue();
    QString getStartTimeValue();
    QString getEndDateValue();
    QString getEndTimeValue();
    bool getShowMonthlyAvg();
    bool getShowMonthlyMinMaxAvg();

signals:
    void timeChanged();
    void showMonthlyMinMaxAvgChanged();
    void showMonthlyAvgChanged();
};

#endif // VIEW_HH
