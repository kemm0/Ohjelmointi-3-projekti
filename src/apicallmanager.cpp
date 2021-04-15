#include "apicallmanager.h"
#include "apicaller.hh"
#include "apicallerfmi.hh"
#include "apicallerfingrid.hh"
#include <QFile>

APICallManager::APICallManager(QObject *parent) :
    QObject(parent),
    apiConfig({})
{
    loadAPIConfig();
}

void APICallManager::fetchData(DataRequest dataRequest)
{
    if (dataRequest.startTime.daysTo(dataRequest.endTime) < 7) {
        createFetchInstance(dataRequest);
    } else {
        for (DataRequest& part : splitRequest(dataRequest))
        {
            createFetchInstance(part);
        }
    }
}

void APICallManager::forwardData(std::shared_ptr<Data> data)
{
    emit dataFetched(data);
}

void APICallManager::forwardErrorMessage(QString errorMessage)
{
    emit requestError(errorMessage);
}

void APICallManager::loadAPIConfig()
{
    QFile apiConfigFile("../kumivene-solutions/apiconfig.txt");

    if (!apiConfigFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open apiconfig.txt file. Make sure it's in the "
        "project root folder");

        emit requestError("Couldn't open apiconfig.txt file. Make sure "
        "it's in the project root folder");
        return;
    }

    QTextStream in(&apiConfigFile);

    while(!in.atEnd()){
        QString line = in.readLine();
        auto parts = line.split("=");
        QString key = parts[0];
        QString value = parts[1];
        apiConfig[key] = value;
    }
}

void APICallManager::createFetchInstance(DataRequest dataRequest)
{
    if(APICallerFMI::dataTypes().contains(dataRequest.datatype)){
        auto api = new APICallerFMI(this);
        connect(api,&APICallerFMI::dataParsed,this,&APICallManager::forwardData);
        connect(api,&APICallerFMI::requestError,this,&APICallManager::forwardErrorMessage);
        api->fetchData(dataRequest);
    }
    else if(APICallerFingrid::dataTypes().contains(dataRequest.datatype)){
        auto api = new APICallerFingrid(apiConfig.value("FINGRID_API_KEY"),this);
        connect(api,&APICallerFingrid::dataParsed,this,&APICallManager::forwardData);
        connect(api,&APICallerFingrid::requestError,this,&APICallManager::forwardErrorMessage);
        api->fetchData(dataRequest);
    }
}

QVector<DataRequest> APICallManager::splitRequest(DataRequest dataRequest)
{
    QVector<DataRequest> parts = {};
    QDateTime split = dataRequest.startTime;
    while (split < dataRequest.endTime)
    {
        DataRequest part;
        part.datatype = dataRequest.datatype;
        part.location = dataRequest.location;
        part.startTime = split;
        if (split.addDays(7) > dataRequest.endTime) {
            split = dataRequest.endTime;
        } else {
            split = split.addDays(7);
        }
        part.endTime = split;
        parts.push_back(part);
    }
    return parts;
}
