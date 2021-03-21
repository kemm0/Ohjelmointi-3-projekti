import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ComboBox {
    currentIndex: 7
    width: 300
    model: ListModel {
        id: datas
        ListElement {text: "Electricity consumption"}
        ListElement {text: "Tentative production prediction"}
        ListElement {text: "Electricity production"}
        ListElement {text: "Wind power production"}
        ListElement {text: "Nuclear power production"}
        ListElement {text: "Hydro power production"}
        ListElement {text: "Power forms percentages"}
        ListElement {text: "Temperature"}
        ListElement {text: "Wind"}
        ListElement {text: "Cloudiness"}
    }
    Component.onCompleted: locationMenu.getModel()
    onCurrentIndexChanged: locationMenu.getModel()
}
