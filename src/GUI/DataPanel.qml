import QtQuick 2.0
/*
  A Panel where the user can choose from many data options. Chosen data is then displayed on the graph
  */
Rectangle{
    border.color: "black"
    border.width: 1
    ListView{
        width: parent.width
        height: parent.height
        model: DataModel{}
        delegate: Text{
            text: name + ": " + value + ": " + latest_update + ": " + graphColor
        }
    }
}
