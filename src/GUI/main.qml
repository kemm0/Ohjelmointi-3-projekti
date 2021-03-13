import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15


Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Upea GUI")
    color: "#e3e3e3"
    TabMenu {
        id: tabs
        width: parent.width
        height: childrenRect.height
        anchors.top: mainWindow.bottom
        anchors.topMargin: 5
    }
    Layouts {
        id: layout
        currentIndex: tabs.currentIndex
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
    }

}
