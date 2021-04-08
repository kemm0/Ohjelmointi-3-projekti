import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */

Item{
    id: weatherPanel
    property alias dataTypeSelection: dataTypesList.currentText
    property alias locationSelection: locationsList.currentText
    clip: true

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
                ListElement {text: "Temperature"}
                ListElement {text: "Average maximum temperature"}
                ListElement {text: "Average minimum temperature"}
                ListElement {text: "Average temperature"}
                ListElement {text: "Observed wind"}
                ListElement {text: "Observed cloudiness"}
                ListElement {text: "Predicted wind"}
                ListElement {text: "Predicted temperature"}
            }
            onCurrentIndexChanged: {
                var selectedText = dataTypesModel.get(currentIndex).text
            }
        }

        ComboBox {
            id: locationsList
            width: 300
            model: ListModel {
                id: locationsModel
                ListElement {text: "Tampere"}
                ListElement {text: "Helsinki"}
                ListElement {text: "Turku"}
                ListElement {text: "Pirkkala"}
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
                    if(!validDateTimeInput(date)){
                        weatherPanel.state = ""
                    }
                }
            }
            TextField {
                id: startTime
                onTextChanged: {
                    var date = Date.fromLocaleTimeString(Qt.locale(), startTime.text, timeFormat)
                    if(!date instanceof Date || isNaN(date)){
                        console.log("Bad date")
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
                    if(!date instanceof Date || isNaN(date)){
                        console.log("Bad date")
                    }
                }
            }
            TextField {
                id: endTime
                onTextChanged: {
                    var date = Date.fromLocaleTimeString(Qt.locale(), endTime.text, timeFormat)
                    if(!date instanceof Date || isNaN(date)){
                        console.log("Bad date")
                    }
                }
            }
        }
        Row{
            Button {
                id: addButton
                text: "Add"
                onClicked: {
                    const newData = {
                                    dataType: dataTypeSelection,
                                    location: locationSelection,
                                    startDate: startDate.text,
                                    startTime: startTime.text,
                                    endDate: endDate.text,
                                    endTime: endTime.text
                                }
                    console.log(newData.startDate, newData.startTime, newData.endDate, newData.endTime)
                    weatherPanel.dataAdded(newData)
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
                                        location: locationSelection,
                                        startDate: startDate.text,
                                        startTime: startTime.text,
                                        endDate: endDate.text,
                                        endTime: endTime.text
                                    }
                        dataSelectionList[dataList.currentIndex] = updatedData
                        dataListModel.set(dataList.currentIndex,updatedData)
                        weatherPanel.dataModified(updatedData)
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
                        weatherPanel.dataRemoved(removedID)
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
    Component.onCompleted: {
        var startDateTime = new Date(Date.now())
        var endDateTime = new Date(Date.now())
        startDateTime.setHours(startDateTime.getHours() - 8)
        startDate.text = startDateTime.toLocaleDateString(Qt.locale(),dateFormat)
        startTime.text = startDateTime.toLocaleTimeString(Qt.locale(),timeFormat)
        endDate.text = endDateTime.toLocaleDateString(Qt.locale(),dateFormat)
        endTime.text = endDateTime.toLocaleTimeString(Qt.locale(),timeFormat)
    }

    Connections{
        target: controller
        function onRequestComplete(data){
            const newData = {
                            id: Math.random(10).toString(),
                            dataType: dataTypeSelection,
                            location: locationSelection,
                            startDate: startDate.text,
                            startTime: startTime.text,
                            endDate: endDate.text,
                            endTime: endTime.text
                        }
            dataSelectionList = dataSelectionList.concat(newData)
            dataListModel.append(newData)
        }
    }
    states: [
        State{
            name: "dataRequestDisabled"
            PropertyChanges {
                target: addButton
                enabled: false
            }
            PropertyChanges {
                target: updateButton
                enabled: false
            }
        }

    ]

    function validDateTimeInput(date){
        if(!date instanceof Date || isNaN(date)){
            return false
        }
        return true
    }
}
