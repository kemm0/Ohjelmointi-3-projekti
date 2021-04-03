import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */

Item{
    property alias startDateText: startDate.text
    property alias startTimeText: startTime.text
    property alias endDateText: endDate.text
    property alias endTimeText: endTime.text
    property alias dataTypeSelection: dataTypesList.currentText
    clip: true
    property var dataSelectionList: []
    property var idCounter: 0
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
                text: new Date().toLocaleDateString(Locale.ShortFormat)
            }
            TextField {
                id: startTime
                text: new Date().toLocaleTimeString(Locale.ShortFormat)
            }
        }
        Label {
            text: "End time"
        }
        Row {
            TextField {
                id: endDate
                text: new Date().toLocaleDateString(Locale.ShortFormat)
            }
            TextField {
                id: endTime
                text: new Date().toLocaleTimeString(Locale.ShortFormat)
            }
        }
        Row{
            Button {
                id: addButton
                text: "Add"
                onClicked: {
                    idCounter = idCounter + 1
                    const newData = {
                                    id: idCounter,
                                    dataType: dataTypeSelection,
                                    startDate: startDateText,
                                    startTime: startTimeText,
                                    endDate: endDateText,
                                    endTime: endTimeText
                                }
                    dataSelectionList = dataSelectionList.concat(newData)
                    dataListModel.append(newData)
                }
            }
            Button {
                id: updateButton
                text: "Update"
                onClicked: {
                    if(dataSelectionList.length != 0){

                        const newData = {
                                        id: dataSelectionList[dataList.currentIndex].id,
                                        dataType: dataTypeSelection,
                                        startDate: startDateText,
                                        startTime: startTimeText,
                                        endDate: endDateText,
                                        endTime: endTimeText
                                    }
                        dataSelectionList[dataList.currentIndex] = newData
                        dataListModel.set(dataList.currentIndex,newData)
                    }
                }
            }
            Button {
                id: clearButton
                text: "Clear"
                onClicked: {
                    const index = dataList.currentIndex
                    dataListModel.remove(index)
                    dataSelectionList = dataSelectionList.splice(index,index)
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
                property var currentDate: new Date()
                name: "prediction24h"
                PropertyChanges {
                    target: startDate
                    text: prediction24h.currentDate.toLocaleDateString(Locale.ShortFormat)
                    enabled: false
                }
                PropertyChanges {
                    target: startTime
                    text: prediction24h.currentDate.toLocaleTimeString(Locale.ShortFormat)
                    enabled: false
                }
                PropertyChanges {
                    target: endDate
                    text: {
                        prediction24h.currentDate.setHours(new Date().getHours() + 24)
                        return prediction24h.currentDate.toLocaleDateString(Locale.ShortFormat)
                    }
                    enabled: false
                }
                PropertyChanges {
                    target: endTime
                    text: {
                        return prediction24h.currentDate.toLocaleTimeString(Locale.ShortFormat)
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
                startDate.text = dataSelectionList[currentIndex].startDate
                startTime.text = dataSelectionList[currentIndex].startTime
                endDate.text = dataSelectionList[currentIndex].endDate
                endTime.text = dataSelectionList[currentIndex].endTime
            }
        }
    }
}
