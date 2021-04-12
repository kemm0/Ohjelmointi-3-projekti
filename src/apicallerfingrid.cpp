#include "apicallerfingrid.hh"

QString APICallerFingrid::baseUrl_ = "https://api.fingrid.fi/v1/variable/%1/events/csv?start_time=%2&end_time=%3";

APICallerFingrid::APICallerFingrid(QObject *parent) : APICaller(parent)
{

}

void APICallerFingrid::fetchData(DataRequest dataRequest)
{

}

void APICallerFingrid::parse(QNetworkReply *reply)
{

}

QString APICallerFingrid::formURL(DataRequest)
{

}
