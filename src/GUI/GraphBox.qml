import QtQuick 2.15
import QtCharts 2.15

/*
  Displays the graph
  */
ChartView {
    antialiasing: true

    LineSeries {
        name: "data1"
        id: lineSeries
        color: "red"
    }
    Component.onCompleted:
    {
        view.lineSeries = lineSeries;
    }
}
