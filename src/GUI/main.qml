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

    TabMenu {
        id: tabs
        width: parent.width
        height: 48
    }
    Layouts {
        id: layout
        currentIndex: tabs.currentIndex
        width: parent.width
        height: parent.height
        anchors.top: tabs.bottom
    }

}
