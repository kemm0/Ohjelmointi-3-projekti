import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
/*
  Contains the Graph and Graph graphMenu
  */

Item{
    clip: true
    ChartView {
        antialiasing: true
        width: parent.width
        height: parent.height - 30
        LineSeries {
            name: "Temperature"
            id: lineSeries
            color: "red"
        }
        Component.onCompleted:
        {
        }
    }
}
