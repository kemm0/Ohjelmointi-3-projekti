import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */
Rectangle{
    border.color: "black"
    border.width: 1
    Column{
        id: options
        RadioButton{
            text: "Temperature"
            checked: true
        }
        Label{
            text: "Start time"
        }
        TextField{
            text: "2021-02-20T22:30:00Z"
        }
        Label{
            text: "End time"
        }
        TextField{
            text: "2021-02-21T10:00:00Z"
        }
        Button {
            id: dataButton
            text: "Refresh"
            onClicked: controller.fetchData()
        }
    }
}
