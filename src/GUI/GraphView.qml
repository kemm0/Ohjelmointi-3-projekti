import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

/*
  Contains the graph and graph toolbar
  */

Item{

    id: root
    property alias chart: chart
    property var chartImg

    clip: true
    ChartView {
        id: chart
        width: parent.width
        height: parent.height - 40
        antialiasing: true

        DateTimeAxis{
            id: xAxis
            min: {
                var date = new Date()
                date.setHours(date.getHours() - 4 )
                return date
            }
            max: new Date()
            tickCount: xTickSlider.value
            format: "d.M.yy h:mm"
        }
        ValueAxis{
            id: yAxis
            min: 0
            max: 1
            tickCount: yTickSlider.value
        }

        Rectangle {
            id: scrollMask
            visible: false
        }
        MouseArea{
            anchors.fill: parent
            onWheel: {
                var zoomAmount = wheel.angleDelta.y / 120
                if(zoomAmount > 0){
                    chart.zoom(1.1)
                }
                if(zoomAmount < 0){
                    chart.zoom(0.9)
                }
            }
            onMouseXChanged: {
                if((mouse.buttons & Qt.LeftButton) == Qt.LeftButton){
                    chart.scrollLeft(mouseX - scrollMask.x)
                    scrollMask.x = mouseX
                }
            }
            onMouseYChanged: {
                if((mouse.buttons & Qt.LeftButton) == Qt.LeftButton){
                    chart.scrollUp(mouseY - scrollMask.y)
                    scrollMask.y = mouseY
                }
            }

            onPressed: {
                if (mouse.button == Qt.LeftButton) {
                    scrollMask.x = mouseX
                    scrollMask.y = mouseY
                }
            }
        }
        LineSeries {
            axisX: xAxis
            axisY: yAxis
        }
        Connections{
            target: controller
            function onRequestComplete(data){
                addSeries(data)
            }
        }
    }
    RowLayout{
        anchors.top: chart.bottom
        height: 40
        Button{
            text: "Reset Zoom"
            onClicked: chart.zoomReset()
        }
        Button{
            text: "Save image"
            onClicked: {
                var component = Qt.createComponent("SaveImageWindow.qml")
                var window = component.createObject(parent)
                window.accepted.connect(saveChartImage)
                window.show()
            }
        }
        Slider{
            id: yTickSlider
            from: 2
            value: 10
            to: 40
            stepSize: 1
            width: 20
        }
        Label{
            text: "x Axis ticks: " + yTickSlider.value.toString()
        }

        Slider{
            id: xTickSlider
            from: 2
            value: 10
            to: 20
            stepSize: 1
        }

        Label{
            text: "y Axis ticks: " + xTickSlider.value.toString()
        }
    }
    function saveChartImage(folder,filename){
        var filePath
        if(OS === 'WINDOWS'){ //OS variable is set in main.cpp
            filePath = folder.substring(8,folder.length) + "/" + filename + ".png"
        }
        else{
            filePath = folder.substring(7,folder.length) + "/" + filename + ".png"
        }

        console.log("saved to: " + filePath)
        chart.grabToImage(function(result){
            result.saveToFile(filePath)
        })
    }
    function addSeries(data) {
        var dates = data.dates
        var values = data.values

        if(dates[0] < xAxis.min) xAxis.min = dates[0]
        if(dates[dates.length-1] > xAxis.max) xAxis.max = dates[dates.length-1]

        var yMin = Math.min(...values)
        var yMax = Math.max(...values)

        if(yMin < yAxis.min) yAxis.min = yMin
        if(yMax > yAxis.max) yAxis.max = yMax

        var name = data.datatype + ' ' + data.id + ' (%1)'.arg(data.unit)

        var series = chart.createSeries(ChartView.SeriesTypeLine, name,xAxis,yAxis)

        for(var i = 0; i < values.length; i++){
            series.append(dates[i].getTime(),values[i])
        }

        for(var j = 0; j < chart.count; j++){
            var s = chart.series(j)
            s.axisX = xAxis
            s.axisY = yAxis
        }
    }
    function removeSeries(index){
        var series = chart.series(index)
        graphView.chart.removeSeries(series)
    }
    function modifySeries(data){
        var series = chart.series(index)
    }
    function changeSeriesName(index, name){
        var series = chart.series(index)
        series.name = name
    }

    Component.onCompleted: {
        chart.removeAllSeries()
    }
}
