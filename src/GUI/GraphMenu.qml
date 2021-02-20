import QtQuick 2.0
import QtQuick.Controls 2.12

/*
  Menu for Graph operations
*/

Rectangle {
    Row {
        Button {
            id: dataButton
            text: "AddData"
            onClicked: view.addData()
        }
    }
}
