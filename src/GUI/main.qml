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
    title: qsTr("Upea GUI")
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
            PowerPanel{
                id: powerpanel
            }
            WeatherPanel{
                id: weatherpanel
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
                graphView.addSeries(dataProperties.id)
            }
            function onDataRemoved(dataID){
                dataRemoved(dataID)
                graphView.removeSeries(dataID)
            }
            function onDataModified(dataProperties){
                dataModified(dataProperties)
                graphView.modifySeries(dataProperties.id)
            }
        }
        Connections{
            target: weatherpanel
            function onDataAdded(dataProperties){
                dataAdded(dataProperties)
                graphView.addSeries(dataProperties.id)
            }
            function onDataRemoved(dataID){
                dataRemoved(dataID)
                graphView.removeSeries(dataID)
            }
            function onDataModified(dataProperties){
                dataModified(dataProperties)
                graphView.modifySeries(dataProperties.id)
            }
        }
    }
}
