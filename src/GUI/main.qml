import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12
import QtCharts 2.15


ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 960
    visible: true
    title: qsTr("App")
    color: "#e3e3e3"
    signal dataAdded(var properties)
    signal dataRemoved(var id)
    signal dataModified(var properties)
    signal savePreferences(var filename, var filepath)
    signal loadPreferences(var filepath)
    signal dataNameChanged(var id, var name)
    signal saveData(var filename, var url, var dataID)
    signal loadData(var filePath)

    property var dataPanels: ({})

    menuBar: MenuBar{
        Menu {
            title: qsTr("Save")
            Action {
                text: qsTr("Preferences")
                onTriggered: {
                    var component = Qt.createComponent("SaveDataWindow.qml")
                    var window = component.createObject(mainWindow)
                    window.accepted.connect(mainWindow.savePreferences)
                    window.show()
                }
            }
        }
        Menu {
            title: qsTr("Load")
            Action {
                text: qsTr("Preferences")
                onTriggered: {
                    var component = Qt.createComponent("LoadDataWindow.qml")
                    var window = component.createObject(mainWindow)
                    window.fileChosen.connect(mainWindow.loadPreferences)
                }
            }
        }
        Menu {
            title: qsTr("Help")
            Action { text: qsTr("About") }
        }
    }

    Rectangle {
        id: settingsView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 350
        TabMenu{
            id: tabs
            width: parent.width
            height: 48
        }
        StackLayout {
            id: layout
            currentIndex: tabs.currentIndex
            width: parent.width
            anchors.top: tabs.bottom
            anchors.bottom: parent.bottom
            clip: true
            DataPanel{
                id: fmiPanel
                dataSource: "FMI"
                dataTypesModel: ListModel{
                    ListElement {text: "Temperature"}
                    ListElement {text: "Average maximum temperature"}
                    ListElement {text: "Average minimum temperature"}
                    ListElement {text: "Average temperature"}
                    ListElement {text: "Observed wind"}
                    ListElement {text: "Observed cloudiness"}
                    ListElement {text: "Predicted wind"}
                    ListElement {text: "Predicted temperature"}
                }
                locationsModel: ListModel {
                    ListElement {text: "Tampere"}
                    ListElement {text: "Helsinki"}
                    ListElement {text: "Turku"}
                    ListElement {text: "Pirkkala"}
                }
            }
            DataPanel{
                id: fingridPanel
                dataSource: "Fingrid"
                dataTypesModel: ListModel {
                    ListElement {text: "Electricity consumption"}
                    ListElement {text: "Electricity production"}
                    ListElement {text: "Electricity consumption forecast 24h"}
                    ListElement {text: "Electricity production forecast 24h"}
                    ListElement {text: "Wind power production"}
                    ListElement {text: "Nuclear power production"}
                    ListElement {text: "Hydro power production"}
                    ListElement {text: "Power forms percentages"}
                }
                locationsModel: ListModel {
                    ListElement {text: "Finland"}
                }
            }
        }
        }

    GraphView{
        anchors.left: settingsView.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        id: graphView
    }

    Component{
        id: dialogComponent
        Dialog {
            id: dialog
            required property var message
            title: "Oops!"
            standardButtons: Dialog.Ok

            Text {
                id: text
                text: message
            }

            onAccepted: close()
            onRejected: close()
        }
    }
    function requestData(dataProperties){
        dataAdded(dataProperties)
        graphView.showMessage("Getting data...")
    }
    function addData(data){
        graphView.showMessage("Rendering...")
        if(dataPanels[data.dataSource]){
            dataPanels[data.dataSource].addData(data)
            graphView.addSeries(data)
            graphView.hideMessage();
        }
        else{
            showErrorMessage("Error: Unknown data source.")
        }
    }
    function removeData(id){
        graphView.removeSeries(id)
        dataRemoved(id)
    }
    function changeDataName(id,name){
        graphView.changeSeriesName(id,name)
    }
    function changeActiveData(id){
        graphView.changeActiveSeries(id)
    }
    function showErrorMessage(errorMessage){
        graphView.hideMessage();
        var dialog = dialogComponent.createObject(mainWindow, {message: errorMessage})
        dialog.open()
    }
    Component.onCompleted: {
        dataPanels[fmiPanel.dataSource] = fmiPanel
        dataPanels[fingridPanel.dataSource] = fingridPanel

        for(const dataSource in dataPanels){
            console.log(dataSource)
            const dataPanel = dataPanels[dataSource]
            dataPanel.dataAdded.connect(requestData)
            dataPanel.dataRemoved.connect(removeData)
            dataPanel.dataNameChanged.connect(changeDataName)
            dataPanel.activeDataChanged.connect(changeActiveData)
            dataPanel.saveData.connect(saveData)
            dataPanel.loadData.connect(loadData)
        }
    }
}
