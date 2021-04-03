import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

FileDialog {
    id: fileDialog
    title: "Please choose a file"
    folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    onAccepted: {
        console.log(fileDialog.file)
        close()
    }
    onRejected: {
        console.log("Canceled")
        close()
    }
    Component.onCompleted: visible = true
}
