#ifndef WEATHERDATA_HH
#define WEATHERDATA_HH
#include "data.hh"

class WeatherData : public Data
{
public:
    explicit WeatherData();

    virtual ~WeatherData();
    void setData(QString id, QString datatype, QString unit,dataVector dataValues) override;
};

#endif // WEATHERDATA_HH
