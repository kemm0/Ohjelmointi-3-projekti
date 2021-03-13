import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

StackLayout {
    Item {
        id: weatherTab
        DataPanel{
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: mainWindow.width/2
            height: mainWindow.height/2
        }
        GraphView{
            id: graphView
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: mainWindow.width/2
            height: mainWindow.height/2
        }
    }
    Item {
        id: electricityTab
    }
    Item {
        id: forecastTab
    }
    Item {
        id: dataTab
    }
}
