import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

/*
  Contains the Graph and Graph graphMenu
  */

Item{
    property var chart: chart
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
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }
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
                /*chart.grabToImage(function(result){
                    chartImg = result
                    var component = Qt.createComponent("SaveImageWindow.qml")
                    var window = component.createObject(parent,{
                                                            image: chartImg
                                                        })
                    window.show()
                    console.log("asd")
                })*/
            }
        }
    }

    Component.onCompleted: {
    }
}
