#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include <memory>
#include "datamodel.hh"
#include "data.hh"
#include "backend.h"

class Controller : public QObject
{
    Q_OBJECT

public slots:
    void sendDataToView(std::shared_ptr<Data> data);
    void test(Data* data);
public:
    explicit Controller(std::shared_ptr<Backend> backend,
                        QObject *parent = nullptr);

    Q_INVOKABLE void getNewData(QVariant properties);
    Q_INVOKABLE void getExistingData();
    Q_INVOKABLE void loadData();
    Q_INVOKABLE void loadPreferences();
    void setView(QObject* view);

signals:
    void getNewData(DataRequest request);
    void requestComplete(QMap<QString,QVariant> data);

private:
    std::shared_ptr<Backend> backend_;
    QObject *view_;

};

#endif // CONTROLLER_HH
