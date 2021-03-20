import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

/*
  Contains the Graph and Graph graphMenu
  */

Item{
    clip: true
    property date minDate: new Date();
    property date maxDate: new Date(Date.now());
    GridLayout{
        anchors.fill: parent
        columns: 2
        id: chartGrid
        ChartView {
            antialiasing: true
            GridLayout.fillHeight: true
            GridLayout.fillWidth: true
            id: chart1

            LineSeries {
                name: "Temperature"
                id: lineSeries1
                color: "red"
                axisX: DateTimeAxis{
                    max: maxDate
                }
            }
        }
        ChartView {
            antialiasing: true
            GridLayout.fillHeight: true
            GridLayout.fillWidth: true
            id: chart2
            LineSeries {
                name: "Temperature"
                id: lineSeries2
                color: "red"
                axisX: DateTimeAxis{
                    max: maxDate
                }
            }
        }
        ChartView {
            antialiasing: true
            GridLayout.fillHeight: true
            GridLayout.fillWidth: true
            id: chart3
            LineSeries {
                name: "Temperature"
                id: lineSeries3
                color: "red"
                axisX: DateTimeAxis{
                    max: maxDate
                }
            }
        }
        ChartView {
            antialiasing: true
            GridLayout.fillHeight: true
            GridLayout.fillWidth: true
            id: chart4
            LineSeries {
                name: "Temperature"
                id: lineSeries4
                color: "red"
                axisX: DateTimeAxis{
                    max: maxDate
                }
            }
        }
        Component.onCompleted: {
            view.addChartFromSeries(lineSeries1);
            view.addChartFromSeries(lineSeries2);
            view.addChartFromSeries(lineSeries3);
            view.addChartFromSeries(lineSeries4);
        }
    }
}
