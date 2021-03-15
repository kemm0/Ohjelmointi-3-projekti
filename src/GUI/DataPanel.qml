import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */
Rectangle{
    border.color: "black"
    border.width: 1
    Column{
        padding: 10
        spacing: 5
        id: options
        Datatype{

        }
        Label{
            text: "Start time"
        }
        Row {
            TextField {
                id: lowerLimitDate
                text: "2021-02-20"
            }
            TextField {
                id: lowerLimitTime
                text: "22:30:00"
            }
        }
        Label{
            text: "End time"
        }
        Row {
            TextField{
                id: upperLimitDate
                text: "2021-02-21"
            }
            TextField{
                id: upperLimitTime
                text: "10:00:00"
            }
        }
        CheckBox{
            checked: false
            text: "Show average (monthly)"
        }
        CheckBox{
            checked: false
            text: "Show average min & max (monthly)"
        }
        Button {
            id: dataButton
            text: "Refresh"
            onClicked: controller.getNewData()
        }
    }
}
