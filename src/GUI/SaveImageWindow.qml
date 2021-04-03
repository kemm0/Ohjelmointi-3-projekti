import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

Window {
    id: window
    width: 300
    height: 300
    visible: true
    title: qsTr("Upea GUI")
    required property var image
    Item{
        anchors.fill: parent
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            width: childrenRect.width
            Layout.alignment: Qt.AlignHCenter
            spacing: 5
            Label{text: "Choose file name: "}
            Row{
                TextField{
                    id: fileNameInput
                }
                Label{text: ".png"}
            }
            Label{
                text: "Choose folder"
            }
            Row{
                TextField{
                    id: folderInput
                }
                Button{
                    id: button
                    text: "Browse"
                    onClicked: {
                        folderDialogComponent.createObject(parent)
                    }
                }
            }
            Button{
                text: "Save"
                onClicked:{
                    //save file
                    //image.url = folderInput.text
                    image.saveToFile(fileNameInput.text + ".png")
                    close()
                }
            }
        }
    }

    Component{
        id: folderDialogComponent
        FolderDialog {
            id: folderDialog
            title: "Please choose a folder"
            options: FolderDialog.ShowDirsOnly
            currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
            onAccepted: {
                console.log("You chose: " + folderDialog.folder)
                folderInput.text = folderDialog.folder
            }
            onRejected: {
                console.log("Canceled")
            }
            Component.onCompleted: visible = true
        }
    }
}
