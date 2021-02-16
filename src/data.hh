#ifndef DATA_HH
#define DATA_HH

#include <QObject>
#include <map>
#include <QNetworkAccessManager>
#include <memory>

class Data
{
public:

    Data(std::shared_ptr<QNetworkAccessManager> manager);

    /**
     * @brief Method used to fetch data from FMI's API
     */
    void fetchdDataFMI();


    /**
     * @brief Method used to fetch data from FinGrid's API
     */
    void fetchDataFinGrid();

private:
    std::shared_ptr<QNetworkAccessManager> manager_;
};

#endif // DATA_HH
