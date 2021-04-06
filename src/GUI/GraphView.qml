import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

/*
  Contains the Graph and Graph graphMenu
  */

Item{
    property alias chart: chart
    property var chartImg
    clip: true
    ChartView {
        id: chart
        width: parent.width
        height: parent.height - 40
        antialiasing: true

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
    }
    function saveChartImage(folder,filename){
        var filePath
        if(OS === 'WINDOWS'){
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
    function addSeries(id) {
        var series = chart.createSeries(ChartView.SeriesTypeLine,id)
        for(var i = 0; i < 5; i++){
            series.append(Math.random(),Math.random())
        }
    }
    function removeSeries(id){
        var series = chart.series(id)
        graphView.chart.removeSeries(series)
    }
    function modifySeries(id){
        var series = chart.series(id)
        series.removePoints(0,series.count)
        for(var i = 0; i < 5; i++){
            series.append(Math.random(),Math.random())
        }
    }

    Component.onCompleted: {
        chart.removeAllSeries()
    }
}
