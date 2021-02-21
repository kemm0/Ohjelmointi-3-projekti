#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include <memory>

class Data;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(std::shared_ptr<Data> data,
                        QObject *parent = nullptr);


    Q_INVOKABLE void fetchData();


signals:


private:
    std::shared_ptr<Data> data_;

};

#endif // CONTROLLER_HH
