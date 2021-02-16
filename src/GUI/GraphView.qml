import QtQuick 2.0

/*
  Contains the Graph and Graph graphMenu
  */

Rectangle{
    border.color: "black"
    border.width: 1
    GraphBox{
        id: graph
        anchors.fill: parent
    }
    GraphMenu{
        id: graphMenu
        anchors.top: graph.bottom
        anchors.left: graph.left
    }
}
