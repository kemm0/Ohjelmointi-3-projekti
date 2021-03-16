import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

StackLayout {
    clip: true
    Item {
        id: weatherTab
        SplitView{
            anchors.fill: parent
            orientation: Qt.Horizontal
            SplitView{
                orientation: Qt.Vertical
                SplitView.minimumWidth: dataPanel.childrenRect.width
                DataPanel{
                    id: dataPanel
                    SplitView.minimumHeight: parent.height/2
                }
                DataList{
                    id: dataList
                }
            }
            GraphView{
                id: graphView
            }

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
