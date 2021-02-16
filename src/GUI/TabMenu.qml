import QtQuick 2.0
import QtQuick.Controls 2.12

/*
  Menu for choosing tabs
*/
Rectangle{
    TabBar {
        TabButton {
            text: "Electricity"
            width: implicitWidth
        }
        TabButton {
            text: "Weather"
            width: implicitWidth
        }
        TabButton {
            text: "Forecast"
            width: implicitWidth
        }
    }

}
