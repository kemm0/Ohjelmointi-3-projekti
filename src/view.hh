#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QLineSeries>
#include <QChart>

class View : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* lineSeries READ getLineSeries WRITE setLineSeries NOTIFY lineSeriesSignal)

public:
    View(QObject* parent = nullptr);
    virtual ~View();

    QtCharts::QLineSeries* getLineSeries() const;
    void setLineSeries(QtCharts::QLineSeries *lineSeries);

    Q_INVOKABLE void addData();
    Q_INVOKABLE void clearData();

signals:
    void lineSeriesSignal();

private:
    QtCharts::QLineSeries* lineSeries_;
    float x = 0;
    float y = 0;
};

#endif // VIEW_HH
