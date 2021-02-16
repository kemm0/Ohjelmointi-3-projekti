import QtQuick 2.15
import QtQuick.Window 2.15


Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Upea GUI")
    color: "#e3e3e3"
    TabMenu{
        id: tabs
        width: parent.width
        height: childrenRect.height
        anchors.top: mainMenu.bottom
        anchors.topMargin: 5
    }
    DataPanel{
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: mainWindow.width/2
        height: mainWindow.height/2
    }
    GraphView{
        width: mainWindow.width/2
        height: mainWindow.height/2
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
    }
}
