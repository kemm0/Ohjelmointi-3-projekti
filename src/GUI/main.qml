import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12
import QtCharts 2.15


Window {
    id: mainWindow
    width: 1280
    height: 960
    visible: true
    title: qsTr("App")
    color: "#e3e3e3"
    signal dataAdded(var properties)
    signal dataRemoved(var id)
    signal dataModified(var properties)
    signal testSignal()

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
                id: weatherpanel
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
                id: powerpanel
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
        Connections{
            target: powerpanel
            function onDataAdded(dataProperties){
                dataAdded(dataProperties)
            }
            function onDataRemoved(id){
                graphView.removeSeries(id)
                dataRemoved(id)
            }
            function onDataModified(dataProperties){
                dataModified(dataProperties)
            }
            function onDataNameChanged(id,name){
                graphView.changeSeriesName(id,name)
            }
        }
        Connections{
            target: weatherpanel
            function onDataAdded(dataProperties){
                dataAdded(dataProperties)
            }
            function onDataRemoved(id){
                graphView.removeSeries(id)
                dataRemoved(id)
            }
            function onDataModified(dataProperties){
                dataModified(dataProperties)
            }
            function onDataNameChanged(id,name){
                graphView.changeSeriesName(id,name)
            }
        }
    }
}
