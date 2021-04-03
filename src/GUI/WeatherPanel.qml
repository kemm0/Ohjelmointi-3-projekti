import QtQuick 2.15
import QtQuick.Controls 2.15
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */

Item{
    property alias startDateText: startDate.text
    property alias startTimeText: startTime.text
    property alias endDateText: endDate.text
    property alias endTimeText: endTime.text
    clip: true

    Column {
        padding: 10
        spacing: 5
        id: options
        ComboBox {
            width: 300
            model: ListModel {
                id: dataTypes
                ListElement {text: "Temperature"}
                ListElement {text: "Average Temperature"}
                ListElement {text: "Average minimum temperature"}
                ListElement {text: "Average maximum temperature"}
                ListElement {text: "Observed wind"}
                ListElement {text: "Observed cloudiness"}
                ListElement {text: "Predicted temperature"}
                ListElement {text: "Predicted wind"}
            }
        }
        ComboBox{
            id: locations
            width: 300
            model: ListModel {
                id: listElements
                ListElement {text: "Tampere"}
                ListElement {text: "Pirkkala"}
                ListElement {text: "Helsinki"}
                ListElement {text: "Turku"}
            }
        }

        Label {
            text: "Start time"
        }
        Row {
            TextField {
                id: startDate
                text: new Date().toLocaleDateString(Locale.ShortFormat)
            }
            TextField {
                id: startTime
                text: new Date().toLocaleTimeString(Locale.ShortFormat)
            }
        }
        Label {
            text: "End time"
        }
        Row {
            TextField {
                id: endDate
                text: new Date().toLocaleDateString(Locale.ShortFormat)
            }
            TextField {
                id: endTime
                text: new Date().toLocaleTimeString(Locale.ShortFormat)
            }
        }
        Row{
            Button {
                id: addButton
                text: "Add"
            }
            Button {
                id: clearButton
                text: "Clear"
            }
        }
        Row {
            Button {
                id: saveButton
                text: "Save Data"
            }
            Button {
                id: loadButton
                text: "Load Data"
            }
        }
    }
}
