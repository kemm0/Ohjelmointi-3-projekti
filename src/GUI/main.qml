import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12


Window {
    id: mainWindow
    width: 1280
    height: 960
    visible: true
    title: qsTr("Upea GUI")
    color: "#e3e3e3"

    DataPanel{
        id: kusi
    }

    Rectangle {
        id: settingsView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 400
        TabMenu{
            id: tabs
            width: parent.width
            height: 48
        }
        Layouts {
            id: layout
            currentIndex: tabs.currentIndex
            width: parent.width
            anchors.top: tabs.bottom
            anchors.bottom: parent.bottom
        }
    }
    GraphView{
        anchors.left: settingsView.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        id: graphView
    }
}
