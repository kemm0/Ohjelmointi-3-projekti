#ifndef API_CALLER_H
#define API_CALLER_H

#include <QObject>

class API_caller : public QObject
{
    Q_OBJECT
public:
    explicit API_caller(QObject *parent = nullptr);

private:

signals:

};

#endif // API_CALLER_H
