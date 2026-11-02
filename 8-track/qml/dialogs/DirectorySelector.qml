import QtQuick
import QtQuick.Dialogs
import QtCore

FolderDialog {
    id: root

    signal folderSelected(url folder)

    currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
    title: "Select a folder to scan"

    onAccepted: root.folderSelected(selectedFolder)
    onRejected: console.log("Folder selection canceled")
}
