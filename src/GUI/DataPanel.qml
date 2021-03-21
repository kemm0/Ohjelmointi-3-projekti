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
    property alias showMonthlyAvg: monthlyAvg.checked
    property alias showMonthlyMinMaxAvg: monthlyMinMaxAvg.checked
    clip: true
    function updateDataProperties(){
        view.setProperties(dataTypeSelection.currentText, locationMenu.currentText, startDateText, startTimeText, endDateText,
                     endTimeText, showMonthlyAvg, showMonthlyMinMaxAvg);
    }

    Column {
        padding: 10
        spacing: 5
        id: options
        Datatype {
            id: dataTypeSelection
        }
        LocationMenu {
            id: locationMenu
        }
        Label {
            text: "Start time"
        }
        Row {
            TextField {
                id: startDate
                text: view.startDateValue
            }
            TextField {
                id: startTime
                text: view.startTimeValue
            }
        }
        Label {
            text: "End time"
        }
        Row {
            TextField {
                id: endDate
                text: view.endDateValue
            }
            TextField {
                id: endTime
                text: view.endTimeValue
            }
        }
        CheckBox {
            id: monthlyAvg
            checked: false
            text: "Show average (monthly)"
        }
        CheckBox {
            id: monthlyMinMaxAvg
            checked: false
            text: "Show average min & max (monthly)"
        }
        Row{
            Button {
                id: addButton
                text: "Add"
                onClicked: {
                    updateDataProperties();
                    controller.getNewData();
                }
            }
            Button {
                id: clearButton
                text: "Clear"
                onClicked: {
                    updateDataProperties();
                    view.clearChart(view.currentChartIndex)
                }
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
