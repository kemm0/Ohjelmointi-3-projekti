import QtQuick 2.15
import QtCharts 2.15
/*
  Contains the Graph and Graph graphMenu
  */

Rectangle{
    border.color: "black"
    border.width: 1
    ChartView {
        antialiasing: true
        anchors.fill: parent
        LineSeries {
            name: "Temperature"
            id: lineSeries
            color: "red"
        }
        Component.onCompleted:
        {
            view.lineSeries = lineSeries;
        }
    }
}
