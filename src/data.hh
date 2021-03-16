#ifndef DATA_HH
#define DATA_HH

#include <QObject>
#include <QDateTime>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
};

#endif // DATA_HH
