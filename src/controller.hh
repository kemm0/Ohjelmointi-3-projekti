#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>
#include <memory>
#include "datamanager.hh"
#include "data.hh"
#include "backend.h"

class Controller : public QObject
{
    Q_OBJECT

public slots:
    void sendDataToView(std::shared_ptr<Data> data);
    void removeData(QVariant id);
    void saveData(QVariant filename, QVariant path, QVariant id);
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
    void saveData(QString filename, QString path, QString id);

private:
    std::shared_ptr<Backend> backend_;
    QObject *view_;

};

#endif // CONTROLLER_HH
