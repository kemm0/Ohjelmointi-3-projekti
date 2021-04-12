import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */

Item{
    id: root
    clip: true

    property alias dataTypeSelection: dataTypesList.currentText
    property alias locationSelection: locationsList.currentText

    property var idCounter: 0

    property string dateFormat: 'dd.MM.yyyy'
    property string timeFormat: 'hh.mm'

    signal dataAdded(var dataProperties)
    signal dataModified(var dataProperties)
    signal dataRemoved(var index, var ID)
    signal dataNameChanged(var index, var name)

    required property var dataTypesModel
    required property var locationsModel

    Column {
        padding: 10
        spacing: 5
        id: options
        ComboBox {
            id: dataTypesList
            width: 300
            model: dataTypesModel
        }

        ComboBox {
            id: locationsList
            width: 300
            model: locationsModel
        }

        Label {
            text: "Start time"
        }
        Row {
            TextField {
                id: startDate
                onTextChanged: {
                    var date = Date.fromLocaleDateString(Qt.locale(), startDate.text, dateFormat)
                    validDateTimeInput(date, startDate)
                }
            }
            TextField {
                id: startTime
                onTextChanged: {
                    var date = Date.fromLocaleTimeString(Qt.locale(), startTime.text, timeFormat)
                    validDateTimeInput(date, startTime)
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
                    validDateTimeInput(date, endDate)
                }
            }
            TextField {
                id: endTime
                onTextChanged: {
                    var date = Date.fromLocaleTimeString(Qt.locale(), endTime.text, timeFormat)
                    validDateTimeInput(date, endTime)
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
                    root.dataAdded(newData)
                }
            }
            Button {
                id: updateButton
                text: "Update"
                onClicked: {
                    if(dataListModel.count != 0){
                        const updatedData = {
                                        id: dataListModel.get(dataList.currentIndex).id,
                                        dataType: dataTypeSelection,
                                        location: locationSelection,
                                        startDate: startDate.text,
                                        startTime: startTime.text,
                                        endDate: endDate.text,
                                        endTime: endTime.text
                                    }
                        dataListModel.set(dataList.currentIndex,updatedData)
                        root.dataModified(updatedData)
                    }
                }
            }
            Button {
                id: clearButton
                text: "Remove"
                onClicked: {
                    if(dataListModel.count != 0){
                        const index = dataList.currentIndex
                        const removedID = dataListModel.get(index).id
                        dataListModel.remove(index)
                        root.dataRemoved(index,removedID)
                    }
                }
            }
        }

        Row {
            Button {
                id: saveButton
                text: "Save Data"
                onClicked: {
                    if(dataListModel.count != 0){
                        var component = Qt.createComponent("SaveDataWindow.qml")
                        var window = component.createObject(parent,{
                                                                dataID: dataListModel.get(dataList.currentIndex).id
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
        delegate:
            TextInput{
                id: textDelegate
                text: dataType + ", " + location + " (%1)".arg(id)
                readOnly: true
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        dataList.currentIndex = index
                    }
                    onDoubleClicked: {
                        parent.enabled = true
                        parent.forceActiveFocus()
                        parent.readOnly = false
                    }
                }
                onAccepted: {
                    parent.focus = false
                    readOnly = true
                    dataNameChanged(dataList.currentIndex, textDelegate.text + ", " +  " (%1)".arg(dataListModel.get(dataList.currentIndex).unit))
                }
        }
        highlight: Rectangle {color: "lightsteelblue"; radius: 5}
        focus: true
        onCurrentIndexChanged: {
            if(dataListModel.count != 0 && dataListModel.get(currentIndex)){
                const dataTypeIndex = dataTypesList.indexOfValue(dataListModel.get(currentIndex).dataType)
                dataTypesList.currentIndex = dataTypeIndex
                const locationIndex = locationsList.indexOfValue(dataListModel.get(currentIndex).location)
                locationsList.currentIndex = locationIndex
                var selectedData = dataListModel.get(currentIndex)
                startDate.text = selectedData.startDate
                startTime.text = selectedData.startTime
                endDate.text = selectedData.endDate
                endTime.text = selectedData.endTime
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
            var dataTypeFound = dataTypeExists(dataTypesModel,data.datatype);
            if(dataTypeFound){
                const newData = {
                                id: data.id,
                                dataType: dataTypeSelection,
                                location: locationSelection,
                                unit: data.unit,
                                startDate: startDate.text,
                                startTime: startTime.text,
                                endDate: endDate.text,
                                endTime: endTime.text
                            }
                dataListModel.append(newData)
                dataList.currentIndex = dataListModel.count - 1
            }
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

    function validDateTimeInput(date,field){
        if(!date instanceof Date || isNaN(date)){
            root.state = "dataRequestDisabled"
            field.color = "red"
        }
        else{
            root.state = ""
            field.color = ""
        }
    }
    function dataTypeExists(model,datatype){
        for(var i = 0; i < model.count; ++i){
            if(model.get(i).text == datatype){
                return true
            }
        }
        return false
    }
}
