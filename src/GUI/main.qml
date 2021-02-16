import QtQuick 2.15
import QtQuick.Window 2.15


Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Upea GUI")
    color: "#e3e3e3"
    Rectangle{
        id: mainMenu
        width: parent.width
        height: mainWindow.height * 0.05
        anchors.top: parent.top
        color: "blue"
        TopMenu{
            anchors.fill: parent
        }
    }
    Rectangle{
        width: parent.width
        height: mainWindow.height * 0.05
        anchors.top: mainMenu.bottom
        color: "red"
        anchors.topMargin: 5
        TabMenu{
            id: tabs
            anchors.fill: parent
        }
    }
    Rectangle{
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: mainWindow.width/2
        height: mainWindow.height/2
        color: "white"
        border.color: "black"
        border.width: 1
        ListView{
            width: parent.width
            height: parent.height
            model: DataList{}
            delegate: Text{
                text: name + ": " + value + ": " + latest_update + ": " + graphColor
            }
        }
    }

    Rectangle{
        width: mainWindow.width/2
        height: mainWindow.height/2
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
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
