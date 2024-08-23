import QtQuick 2.7
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 6.7
import Qt.labs.folderlistmodel 2.1

Rectangle {
    id: root
    anchors.fill: parent
    color: "#2e2e2e"

    ListModel {
        id: imageModel
    }

    FolderDialog {
        id: folderDialog
        title: "Choose a folder"
        onAccepted: {
            var folderUrl = folderDialog.selectedFolder;
            if (folderUrl !== "") {
                console.log("Selected folder URL: " + folderUrl)
                loadImages(folderUrl)
            } else {
                console.log("Error: No folder URL selected")
            }
        }
        onRejected: {
            console.log("Folder dialog was rejected")
        }
    }

    FolderListModel {
        id: folderListModel
        folder: ""
        nameFilters: ["*.png", "*.jpg", "*.jpeg"]

        onCountChanged: {
            if (folderListModel.count > 0) {
                imageModel.clear();
                console.log("Folder path: " + folderListModel.folder);
                console.log("Total files in folder: " + folderListModel.count);

                for (var i = 0; i < folderListModel.count; i++) {
                    var file = folderListModel.get(i, "fileURL");
                    if (file) {
                        var filePath = file.toString();
                        console.log("File found: " + filePath);
                        imageModel.append({"filePath": filePath});
                    } else {
                        console.log("Error: file at index " + i + " is undefined.");
                    }
                }

                console.log("Total images loaded into model: " + imageModel.count);
            } else {
                console.log("No files found in the folder.");
            }
        }
    }

    function loadImages(folderPath) {
        if (!folderPath || folderPath === "") {
            console.log("Invalid folder path provided: " + folderPath);
            return;
        }

        folderListModel.folder = folderPath;
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            Layout.fillWidth: true
            Button {
                text: "Choose Folder"
                onClicked: folderDialog.open()
                background: Rectangle {
                    color: "#444444"
                }
                contentItem: Text {
                    text: "Choose Folder"
                    color: "#ffffff"
                }
            }
            ComboBox {
                id: viewSelector
                model: ["List View", "Table View", "Path View"]
                background: Rectangle {
                    color: "#444444"
                }
                contentItem: Text {
                    text: viewSelector.currentText
                    color: "#ffffff"
                }
            }
        }

        Loader {
            id: viewLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 50
            sourceComponent: viewSelector.currentIndex === 0 ? listViewComponent :
                            viewSelector.currentIndex === 1 ? tableViewComponent :
                            pathViewComponent
        }
    }

    Component {
        id: listViewComponent
        ListView {
            id: list
            Layout.minimumWidth: 100
            Layout.preferredWidth: 150
            Layout.maximumWidth: 250

            width: 150
            height: parent.height
            model: imageModel
            spacing: 2

            delegate: Item {
                width: list.width
                height: 60
                Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "#3e3e3e"
                    border.color: "#555555"
                    radius: 5
                    Row {
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 10
                        Image {
                            source: filePath
                            width: 50
                            height: 50
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        enlargedImageSource.source = filePath
                        enlargedImage.visible = true
                    }
                }
            }

            highlight: Rectangle {
                color: "#555555"
                radius: 5
            }
            highlightMoveDuration: 50
        }
    }

    Component {
        id: tableViewComponent
        GridView {
            id: grid
            cellWidth: 120
            cellHeight: 120
            model: imageModel

            delegate: Item {
                width: grid.cellWidth
                height: grid.cellHeight
                Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "#3e3e3e"
                    border.color: "#555555"
                    radius: 5
                    Image {
                        source: filePath
                        width: 100
                        height: 100
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        enlargedImageSource.source = filePath
                        enlargedImage.visible = true
                    }
                }
            }
        }
    }

    Component {
        id: pathViewComponent
        PathView {
            id: pathView
            model: imageModel
            pathItemCount: 10
            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            focus: true

            path: Path {
                startX: 0; startY: 0
                PathAttribute { name: "iconScale"; value: 1.0 }
                PathLine { x: 100; y: 0 }
                PathAttribute { name: "iconScale"; value: 0.7 }
                PathLine { x: 200; y: 0 }
                PathAttribute { name: "iconScale"; value: 0.5 }
                PathLine { x: 300; y: 0 }
                PathAttribute { name: "iconScale"; value: 0.3 }
                PathLine { x: 400; y: 0 }
                PathAttribute { name: "iconScale"; value: 0.1 }
            }

            delegate: Item {
                width: 100
                height: 100

                property real iconScale: 1.0

                onIconScaleChanged: {
                    iconScale = model.iconScale !== undefined ? model.iconScale : 1.0;
                }

                scale: iconScale

                Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "#3e3e3e"
                    border.color: "#555555" 
                    radius: 5
                    Image {
                        source: filePath
                        width: 100
                        height: 100
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        enlargedImageSource.source = filePath
                        enlargedImage.visible = true
                    }
                }
            }
        }
    }

    Rectangle {
        id: enlargedImage
        color: "#1e1e1e"
        opacity: 0.95
        visible: false
        anchors.fill: parent

        Image {
            id: enlargedImageSource
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: ""
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                enlargedImage.visible = false
            }
        }
    }
}