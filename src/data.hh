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
     */
    void fetchDataFinGrid(const QString &url);

private Q_SLOTS:
    void downloadCompleted(QNetworkReply *);
    void error(QNetworkReply::NetworkError code);
private:
    QNetworkAccessManager *manager_;
};

#endif // DATA_HH