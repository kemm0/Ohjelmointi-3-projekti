import QtQuick 2.15
import QtQuick.Controls 2.12

/*
  Menu for choosing tabs
*/
TabBar {
    TabButton {
        text: "Weather"
        width: implicitWidth
    }
    TabButton {
        text: "Electricity"
        width: implicitWidth
    }
    TabButton {
        text: "Forecast"
        width: implicitWidth
    }
    TabButton {
        text: "Data"
        width: implicitWidth
    }
}
