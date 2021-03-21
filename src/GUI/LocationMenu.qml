import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ComboBox {
    currentIndex: 0
    width: 300
    model: ListModel {
        id: listElements
        ListElement {text: "Suomi"}
    }

    function getModel() {
        if (dataTypeSelection.currentIndex < 6){
            listElements.clear();
            listElements.append({text: "Finland"})
            currentIndex = 0;
        } else {
            listElements.clear();
            listElements.append({text: "Tampere"});
            listElements.append({text: "Helsinki"});
            listElements.append({text: "Turku"});
            listElements.append({text: "Pirkkala"});
            currentIndex = 0;
        }
    }
}
