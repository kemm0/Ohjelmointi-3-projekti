import QtQuick 2.15
import QtQuick.Window 2.15


Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Upea GUI")
    color: "#e3e3e3"
    GraphMenu{
        id: topMenu
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Rectangle{
        width: mainWindow.width/2
        height: mainWindow.height/2
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        GraphBox{
            id: graph
            anchors.fill: parent
        }
        GraphMenu{
            id: graphMenu
            anchors.top: graph.bottom
            anchors.left: graph.left
        }
    }
}
