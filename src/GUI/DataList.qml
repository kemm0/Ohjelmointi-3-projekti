import QtQuick 2.0
import QtQuick.Controls 2.15

ListView {
    // toimii nuolinäppäimillä mutta ei vielä klikkauksella
    // myös rippaa jos klikkaa jonnekin muualle ikkunassa
    id: listView
    clip: true
    model: ListModel{
        ListElement{
            chartId: "Chart 1"
        }
        ListElement{
            chartId: "Chart 2"
        }
        ListElement{
            chartId: "Chart 3"
        }
    }

    delegate: Text{
            id: listDelegate
            text: chartId
    }
    highlight: Rectangle {
        color: "lightsteelblue";
        radius: 5;
    }
    focus: true
}
