import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

// a dialog window for selecting file name and folder

Window {
    id: window
    width: 300
    height: 300
    visible: true
    title: qsTr("Save data to file")
    signal accepted(var filename, var url)
    Item{
        anchors.fill: parent
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            width: childrenRect.width
            Layout.alignment: Qt.AlignHCenter
            spacing: 5
            Label{text: "Choose file name: "}
            TextField{
                id: fileNameInput
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
                    accepted(fileNameInput.text, folderInput.text)
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
            currentFolder: StandardPaths.writableLocation(
                               StandardPaths.DocumentsLocation)
            onAccepted: {
                folderInput.text = folderDialog.folder
            }
            Component.onCompleted: visible = true
        }
    }
}
