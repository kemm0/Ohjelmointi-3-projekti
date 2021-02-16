import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Button {
        id: button1
        text: "Button 1"
        anchors.left: parent.left
    }
    Button {
        text: "Button 2"
        anchors.left: button1.right
    }
}
