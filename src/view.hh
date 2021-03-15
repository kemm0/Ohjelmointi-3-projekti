#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QLineSeries>
#include <QChart>
#include <QDateTime>
#include <QtQuick>

class View : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* lineSeries READ getLineSeries WRITE setLineSeries NOTIFY lineSeriesSignal)
    Q_PROPERTY(QString startDateValue READ getStartDateValue NOTIFY timeChanged)
    Q_PROPERTY(QString startTimeValue READ getStartTimeValue NOTIFY timeChanged)
    Q_PROPERTY(QString endDateValue READ getEndDateValue NOTIFY timeChanged)
    Q_PROPERTY(QString endTimeValue READ getEndTimeValue NOTIFY timeChanged)

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();

    QString getStartDateValue();
    QString getStartTimeValue();
    QString getEndDateValue();
    QString getEndTimeValue();

    void setTime(QString startDate, QString startTime, QString endDate, QString endTime);

    QtCharts::QLineSeries* getLineSeries() const;
    void setLineSeries(QtCharts::QLineSeries *lineSeries);

    Q_INVOKABLE void setData(std::vector<std::pair<QDateTime,qreal>>);
    Q_INVOKABLE void clearData();

signals:
    void lineSeriesSignal();
    void timeChanged();

private:
    QtCharts::QLineSeries* lineSeries_;
    QDateTime startTime_;
    QDateTime endTime_;
};

#endif // VIEW_HH
