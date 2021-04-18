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

    property var seriesMap: ({})
    property var activeSeries
    property int xScaleZoom: 0
    property int yScaleZoom: 0

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
        Rectangle {
            id: posInfo
            visible: false
            width: posInfoText.implicitWidth
            height: posInfoText.implicitHeight
            Text{
                id: posInfoText
                property var date: new Date()
                text: ""
            }
        }
        Rectangle {
            id: info
            visible: false
            anchors.horizontalCenter: chart.horizontalCenter
            anchors.verticalCenter: chart.verticalCenter
            width: chart.width / 2
            height: chart.height / 2
            Text{
                id: infoText
                anchors.horizontalCenter: info.horizontalCenter
                anchors.verticalCenter: info.verticalCenter
                text: ""
            }
        }
        Rectangle{
            id: recZoom
            border.color: "steelblue"
            border.width: 1
            color: "steelblue"
            opacity: 0.3
            visible: false
            transform: Scale { origin.x: 0; origin.y: 0; xScale: xScaleZoom; yScale: yScaleZoom}
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPositionChanged: {
                if(activeSeries){
                    posInfo.visible = true
                    var p = Qt.point(mouse.x, mouse.y)
                    posInfo.x = mouse.x + 20
                    posInfo.y = mouse.y + 20
                    var chartpoint = chart.mapToValue(p, activeSeries)
                    posInfoText.date.setTime(chartpoint.x)
                    posInfoText.text = posInfoText.date.toString()
                    .substring(0,21) + ", " + chartpoint.y.toFixed(2)
                }
            }
            onExited: {
                posInfo.visible = false
            }
            onReleased: {
                if(mouse.button == Qt.RightButton){
                    var x = (mouseX >= recZoom.x) ? recZoom.x : mouseX
                    var y = (mouseY >= recZoom.y) ? recZoom.y : mouseY
                    chart.zoomIn(Qt.rect(x, y, recZoom.width, recZoom.height));
                    recZoom.visible = false;
                }
            }

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

                if((mouse.buttons & Qt.RightButton) == Qt.RightButton){
                    if (mouseY - recZoom.y >= 0) {
                        yScaleZoom = 1;
                        recZoom.height = mouseY - recZoom.y;
                    } else {
                        yScaleZoom = -1;
                        recZoom.height = recZoom.y - mouseY;
                    }
                }
                if((mouse.buttons & Qt.LeftButton) == Qt.LeftButton){
                    chart.scrollLeft(mouseX - scrollMask.x)
                    scrollMask.x = mouseX
                }
            }
            onMouseYChanged: {
                if((mouse.buttons & Qt.RightButton) == Qt.RightButton){
                    if (mouseX - recZoom.x >= 0) {
                        xScaleZoom = 1;
                        recZoom.width = mouseX - recZoom.x;
                    } else {
                        xScaleZoom = -1;
                        recZoom.width = recZoom.x - mouseX;
                    }
                }
                if((mouse.buttons & Qt.LeftButton) == Qt.LeftButton){
                    chart.scrollUp(mouseY - scrollMask.y)
                    scrollMask.y = mouseY
                }
            }

            onPressed: {
                if(mouse.button == Qt.RightButton){
                    recZoom.x = mouseX;
                    recZoom.y = mouseY;
                    recZoom.visible = true;
                }
                if (mouse.button == Qt.LeftButton) {
                    scrollMask.x = mouseX
                    scrollMask.y = mouseY
                }
            }
        }
        LineSeries {
            visible: false
            axisX: xAxis
            axisY: yAxis
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
        if(Qt.platform.os === 'windows'){
            filePath = folder.substring(8,folder.length) + "/" + filename + ".png"
        }
        else{
            filePath = folder.substring(7,folder.length) + "/" + filename + ".png"
        }
        chart.grabToImage(function(result){
            result.saveToFile(filePath)
        })
    }
    function addSeries(data) {
        var dates = data.dates
        var values = data.values
        xAxis.min = dates[0]
        xAxis.max = dates[dates.length-1]

        var yMin = Math.min(...values)
        var yMax = Math.max(...values)

        if(yMin < yAxis.min) yAxis.min = yMin
        if(yMax > yAxis.max) yAxis.max = yMax

        var name = data.datatype + ', ' + data.location + ' (%1)'.arg(data.id) + ' (%1)'.arg(data.unit)

        var series = chart.createSeries(ChartView.SeriesTypeLine, name,xAxis,yAxis)

        series.useOpenGL = true

        for(var i = 0; i < values.length; i++){
            series.append(dates[i].getTime(),values[i])
        }

        seriesMap[data.id] = series
    }
    function removeSeries(id){
        var series = chart.series(seriesMap[id].name)
        graphView.chart.removeSeries(series)
        delete seriesMap[id]
    }
    function modifySeries(data){
        var series = chart.series(index)
    }
    function changeSeriesName(id, name){
        var series = chart.series(seriesMap[id].name)
        series.name = name
    }
    function changeActiveSeries(id){
        if(seriesMap[id]){
            activeSeries = seriesMap[id]
        }
    }
    function showMessage(message){
        info.visible = true
        infoText.text = message
    }
    function hideMessage(){
        info.visible = false;
    }

    Component.onCompleted: {
        chart.removeAllSeries()
    }
}
