import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0

// a dialog for loading a file

FileDialog {
    id: fileDialog
    title: "Load data from a file"
    folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    signal fileChosen(var filePath)
    onAccepted: {
        fileChosen(fileDialog.file)
        close()
    }
    onRejected: {
        close()
    }
    Component.onCompleted: visible = true
}
