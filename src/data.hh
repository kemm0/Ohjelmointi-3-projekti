#ifndef DATA_HH
#define DATA_HH

#include <QObject>
#include <QDateTime>
#include "Datatypes.h"

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
};

#endif // DATA_HH
