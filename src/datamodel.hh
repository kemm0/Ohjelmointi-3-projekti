#ifndef DATAMODEL_HH
#define DATAMODEL_HH

#include <QObject>

class DataModel : public QObject
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);

signals:

};

#endif // DATAMODEL_HH
