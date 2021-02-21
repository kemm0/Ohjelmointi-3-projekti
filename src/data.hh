#ifndef DATA_HH
#define DATA_HH

#include <QObject>
#include <map>
#include <memory>
#include <iostream>
#include <QApplication>
#include <QNetworkReply>
#include <QDateTime>

class QNetworkAccessManager;

class Data : public QObject
{
    Q_OBJECT
public:

    explicit Data(QObject *parent = nullptr);


    /**
     * @brief Method used to fetch data from FMI's API
     * @param url Url of the API
     */
    void fetchData(const QString &url);

    /**
     * @brief Used to return the values vector
     * @return "values" -vector
     */
    std::vector<std::pair<QDateTime,qreal>> getValues();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply *reply);
    void error(QNetworkReply::NetworkError error);
private:
    QNetworkAccessManager *manager_;
    std::vector<qreal> temps;
    std::vector<QDateTime> dates;

    std::vector<std::pair<QDateTime,qreal>> values;
};

#endif // DATA_HH
