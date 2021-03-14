#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QLineSeries>
#include <QChart>
#include <QDateTime>

class View : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* lineSeries READ getLineSeries WRITE setLineSeries NOTIFY lineSeriesSignal)

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();

    QtCharts::QLineSeries* getLineSeries() const;
    void setLineSeries(QtCharts::QLineSeries *lineSeries);

    Q_INVOKABLE void setData(std::vector<std::pair<QDateTime,qreal>>);
    Q_INVOKABLE void clearData();

signals:
    void lineSeriesSignal();

private:
    QtCharts::QLineSeries* lineSeries_;
    QDateTime upperLimitTime_;
    QDateTime lowerLimitTime_;
};

#endif // VIEW_HH
