#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include <memory>
#include "data.hh"
#include "view.hh"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Data* data,
                        View* view,
                        QObject *parent = nullptr);


    Q_INVOKABLE void fetchData();


signals:


private:
    Data* data_;
    View* view_;

};

#endif // CONTROLLER_HH
