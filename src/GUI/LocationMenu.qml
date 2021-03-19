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
        if (dataTypeSelection.currentIndex < 7){
            listElements.clear();
            listElements.append({text: "Suomi"})
            currentIndex = 0;
        } else {
            listElements.clear();
            listElements.append({text: "Hervanta"});
            listElements.append({text: "Tampere"});
            listElements.append({text: "lappeen Ranta"});
            listElements.append({text: "turku"});
            listElements.append({text: "Hese"});
            currentIndex = 0;
        }
    }
}
