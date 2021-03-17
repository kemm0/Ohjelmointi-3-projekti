import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

StackLayout {
    clip: true
    Item {
        id: chart1
        DataPanel{
            id: dataPanel1
            anchors.fill: parent
        }
    }
    Item {
        id: chart2
        DataPanel{
            id: dataPanel2
            anchors.fill: parent
        }
    }
    Item {
        id: chart3
        DataPanel{
            id: dataPanel3
            anchors.fill: parent
        }
    }
    Item {
        id: chart4
        DataPanel{
            id: dataPanel4
            anchors.fill: parent
        }
    }
}
