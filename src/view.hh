#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QLineSeries>
#include <QChart>
#include <QDateTime>
#include "data.hh"

class View : public QObject
{
    Q_OBJECT

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();

    Q_INVOKABLE void setChartData(QString chart_id,std::vector<std::shared_ptr<Data>> data);
    Q_INVOKABLE void removeChart(QString chart_id);
    Q_INVOKABLE void addChart(std::vector<std::shared_ptr<Data>> data);
    Q_INVOKABLE void changeGridSize(int size);

private:
    std::map<QString,std::vector<QtCharts::QLineSeries*>> chartData;
    QDateTime upperLimitTime_;
    QDateTime lowerLimitTime_;
};

#endif // VIEW_HH
