import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */

Item{
    id: powerPanel
    property alias dataTypeSelection: dataTypesList.currentText
    clip: true

    property var startDateTime: new Date()
    property var endDateTime: new Date()

    property var dataSelectionList: []
    property var idCounter: 0

    property string dateFormat: 'dd.MM.yyyy'
    property string timeFormat: 'hh.mm'

    signal dataAdded(var dataProperties)
    signal dataModified(var dataProperties)
    signal dataRemoved(var ID)

    Column {
        padding: 10
        spacing: 5
        id: options
        ComboBox {
            id: dataTypesList
            width: 300
            model: ListModel {
                id: dataTypesModel
                ListElement {text: "Electricity consumption"}
                ListElement {text: "Electricity production"}
                ListElement {text: "Electricity consumption forecast 24h"}
                ListElement {text: "Electricity production forecast 24h"}
                ListElement {text: "Wind power production"}
                ListElement {text: "Nuclear power production"}
                ListElement {text: "Hydro power production"}
                ListElement {text: "Power forms percentages"}
            }
            onCurrentIndexChanged: {
                var selectedText = dataTypesModel.get(currentIndex).text
                if(selectedText === "Electricity consumption forecast 24h"
                        || selectedText === "Electricity production forecast 24h"){
                    options.state = "prediction24h"
                }
                else{
                    options.state = ""
                }
            }
        }

        Label {
            text: "Start time"
        }
        Row {
            TextField {
                id: startDate
                onTextChanged: {
                    var date = Date.fromLocaleDateString(Qt.locale(), startDate.text, dateFormat)
                    if(date instanceof Date && !isNaN(date)){
                        startDateTime.setFullYear(date.getFullYear())
                        startDateTime.setMonth(date.getMonth())
                        startDateTime.setDate(date.getDate())
                    }
                }
            }
            TextField {
                id: startTime
                onTextChanged: {
                    var date = Date.fromLocaleTimeString(Qt.locale(), startTime.text, timeFormat)
                    if(date instanceof Date && !isNaN(date)){
                        startDateTime.setHours(date.getHours())
                        startDateTime.setMinutes(date.getMinutes())
                    }
                }
            }
        }
        Label {
            text: "End time"
        }
        Row {
            TextField {
                id: endDate
                onTextChanged: {
                    var date = Date.fromLocaleDateString(Qt.locale(), endDate.text, dateFormat)
                    if(date instanceof Date && !isNaN(date)){
                        endDateTime.setFullYear(date.getFullYear())
                        endDateTime.setMonth(date.getMonth())
                        endDateTime.setDate(date.getDate())
                    }
                }
            }
            TextField {
                id: endTime
                onTextChanged: {
                    var date = Date.fromLocaleTimeString(Qt.locale(), endTime.text, timeFormat)
                    if(date instanceof Date && !isNaN(date)){
                        endDateTime.setHours(date.getHours())
                        endDateTime.setMinutes(date.getMinutes())
                    }
                }
            }
        }
        Row{
            Button {
                id: addButton
                text: "Add"
                onClicked: {
                    idCounter = idCounter + 1
                    const newData = {
                                    id: idCounter.toString(),
                                    dataType: dataTypeSelection,
                                    startDate: new Date(startDateTime.getTime()),
                                    endDate: new Date(endDateTime.getTime())
                                }
                    dataSelectionList = dataSelectionList.concat(newData)
                    dataListModel.append(newData)
                    powerPanel.dataAdded(newData)
                }
            }
            Button {
                id: updateButton
                text: "Update"
                onClicked: {
                    if(dataSelectionList.length != 0){

                        const updatedData = {
                                        id: dataSelectionList[dataList.currentIndex].id,
                                        dataType: dataTypeSelection,
                                        startDate: new Date(startDateTime.getTime()),
                                        endDate: new Date(endDateTime.getTime())
                                    }
                        dataSelectionList[dataList.currentIndex] = updatedData
                        dataListModel.set(dataList.currentIndex,updatedData)
                        powerPanel.dataModified(updatedData)
                    }
                }
            }
            Button {
                id: clearButton
                text: "Remove"
                onClicked: {
                    if(dataSelectionList.length != 0){
                        const index = dataList.currentIndex
                        const removedID = dataSelectionList[index].id
                        dataListModel.remove(index)
                        dataSelectionList.splice(index,1)
                        powerPanel.dataRemoved(removedID)
                    }
                }
            }
        }

        Row {
            Button {
                id: saveButton
                text: "Save Data"
                onClicked: {
                    if(dataSelectionList.length != 0){
                        var component = Qt.createComponent("SaveDataWindow.qml")
                        var window = component.createObject(parent,{
                                                                dataID: dataSelectionList[dataList.currentIndex].id
                                                            })
                        window.show()
                    }
                }
            }
            Button {
                id: loadButton
                text: "Load Data"
                onClicked: {
                    var component = Qt.createComponent("LoadDataWindow.qml")
                    var window = component.createObject()
                }
            }
        }
        states: [
            State {
                id: prediction24h
                property var currentDate: new Date(Date.now())
                name: "prediction24h"
                PropertyChanges {
                    target: startDate
                    text: prediction24h.currentDate.toLocaleDateString(Qt.locale(),dateFormat)
                    enabled: false
                }
                PropertyChanges {
                    target: startTime
                    text: prediction24h.currentDate.toLocaleTimeString(Qt.locale(),timeFormat)
                    enabled: false
                }
                PropertyChanges {
                    target: endDate
                    text: {
                        prediction24h.currentDate.setHours(prediction24h.currentDate.getHours() + 24)
                        return prediction24h.currentDate.toLocaleDateString(Qt.locale(),dateFormat)
                    }
                    enabled: false
                }
                PropertyChanges {
                    target: endTime
                    text: {
                        return prediction24h.currentDate.toLocaleTimeString(Qt.locale(),timeFormat)
                    }
                    enabled: false
                }
            }

        ]
    }

    ListView{
        id: dataList
        width: parent.width
        height: parent.height-options.height
        anchors.top: options.bottom
        model: ListModel{
            id: dataListModel
        }
        delegate: Text{
            text: dataType + " (" + id + ")"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    dataList.currentIndex = index
                    dataList.forceActiveFocus()
                }
            }
        }
        highlight: Rectangle {color: "lightsteelblue"; radius: 5}
        focus: true
        onCurrentIndexChanged: {
            if(dataSelectionList.length != 0 && dataSelectionList[currentIndex]){
                const index = dataTypesList.indexOfValue(dataSelectionList[currentIndex].dataType)
                dataTypesList.currentIndex = index
                startDate.text = dataSelectionList[currentIndex].startDate.toLocaleDateString(Qt.locale(),dateFormat)
                startTime.text = dataSelectionList[currentIndex].startDate.toLocaleTimeString(Qt.locale(),timeFormat)
                endDate.text = dataSelectionList[currentIndex].endDate.toLocaleDateString(Qt.locale(),dateFormat)
                endTime.text = dataSelectionList[currentIndex].endDate.toLocaleTimeString(Qt.locale(),timeFormat)
            }
        }
    }
    Component.onCompleted: {
        startDateTime.setHours(startDateTime.getHours() - 4)
        startDate.text = startDateTime.toLocaleDateString(Qt.locale(),dateFormat)
        startTime.text = startDateTime.toLocaleTimeString(Qt.locale(),timeFormat)
        endDate.text = endDateTime.toLocaleDateString(Qt.locale(),dateFormat)
        endTime.text = endDateTime.toLocaleTimeString(Qt.locale(),timeFormat)
    }
}
