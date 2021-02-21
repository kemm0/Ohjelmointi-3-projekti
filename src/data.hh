#ifndef DATA_HH
#define DATA_HH

#include <QObject>
#include <map>
#include <memory>
#include <iostream>
#include <QApplication>
#include <QNetworkReply>

class QNetworkAccessManager;

class Data : public QObject
{
    Q_OBJECT
public:

    explicit Data(QObject *parent = nullptr);

    /**
     * @brief Method used to fetch data from FMI's API
     */
    void fetchdDataFMI();


    /**
     * @brief Method used to fetch data from FinGrid's API
     * @param url Url of the API
     */
    void fetchData(const QString &url);

    /**
     * @brief Used to return the values vector
     * @return "values" -vector
     */
    std::vector<std::pair<QString,double>> returnValues();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply *reply);
    void error(QNetworkReply::NetworkError error);
private:
    QNetworkAccessManager *manager_;
    std::vector<double> temps;
    std::vector<QString> dates;

    std::vector<std::pair<QString,double>> values;
};

#endif // DATA_HH
