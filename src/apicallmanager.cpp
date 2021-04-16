#include "apicallmanager.h"
#include "apicaller.hh"
#include "apicallerfmi.hh"
#include "apicallerfingrid.hh"
#include <QFile>
#include <cmath>

APICallManager::APICallManager(QObject *parent) :
    QObject(parent),
    apiConfig_({})
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
    if (!data->isSplit()) { emit dataFetched(data); }
    else {
        auto splitData = incompleteRequests_.find(data->getSplitId().first);
        splitData->second.insert(data->getSplitId().second, data);
        qDebug() << splitData->second.size() << splitData->first;
        if (splitData->second.size() == splitData->first) {
            std::vector<std::pair<QDateTime, qreal>> requestValues;
            for (auto part : splitData->second){
                auto partValues = part->getDataValues();
                requestValues.insert(requestValues.end(), partValues.begin(), partValues.end());
            }
            data->setDataValues(requestValues);
            emit dataFetched(data);
        }
    }
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
        apiConfig_[key] = value;
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
        auto api = new APICallerFingrid(apiConfig_.value("FINGRID_API_KEY"),this);
        connect(api,&APICallerFingrid::dataParsed,this,&APICallManager::forwardData);
        connect(api,&APICallerFingrid::requestError,this,&APICallManager::forwardErrorMessage);
        api->fetchData(dataRequest);
    }
}

QVector<DataRequest> APICallManager::splitRequest(DataRequest dataRequest)
{
    QVector<DataRequest> parts = {};
    QDateTime split = dataRequest.startTime;
    splitId_.first++;
    int splits = ceil(dataRequest.startTime.daysTo(dataRequest.endTime) / 7);
    QMap<int, std::shared_ptr<Data>> splitData = {};
    incompleteRequests_.insert(splitId_.first, qMakePair(splits, splitData));
    while (split < dataRequest.endTime){
        DataRequest part;
        part.isSplit = true;
        part.splitId = qMakePair(splitId_.first, splitId_.second++);
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
