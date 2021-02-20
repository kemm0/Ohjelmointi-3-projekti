#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

signals:

};

#endif // CONTROLLER_HH
