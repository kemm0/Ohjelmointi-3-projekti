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

public:
    explicit View(QObject* parent = nullptr);
    virtual ~View();

private:

signals:
};

#endif // VIEW_HH
