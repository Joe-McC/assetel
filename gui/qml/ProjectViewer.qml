import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs
import Qt.labs.platform
import QtQuick.Window
import QtQml.XmlListModel


Page {
    id: projectviewer
    //
    // Toolbar with buttons
    //
    property int layerviewwidth: 300

    header: ToolBar {
        id: toolbar
        height: 48

        //
        // Background gradient
        //
        Rectangle {
            border.width: 1
            border.color: palette.midlight

            gradient: Gradient {
                GradientStop { position: 0; color: "#21373f" }
                GradientStop { position: 1; color: "#11272f" }
            }

            anchors {
                fill: parent
                topMargin: -border.width
                leftMargin: -border.width * 10
                rightMargin: -border.width * 10
            }
        }

        //
        // Toolbar controls
        //
        FileDialog {
            id: loadDialog
            fileMode: FileDialog.OpenFile
            selectedNameFilter.index: 1
            nameFilters: ["Text files (*.xml)"]
            folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
            onAccepted: {
                Cpp_Misc_My_Document.openDocument(currentFile)
            }
        }

        FileDialog {
            id: newDialog
            fileMode: FileDialog.OpenFile
            selectedNameFilter.index: 1
            nameFilters: ["Text files (*.xml)"]
            folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
            onAccepted: {
                Cpp_Misc_My_Document.openDocument(currentFile)
            }
        }

        FileDialog {
            id: saveDialog
            fileMode: FileDialog.SaveFile
            selectedNameFilter.index: 1
            //filename: Cpp_Misc_My_Document.
            //nameFilters: [Cpp_Misc_My_Document.getFilename]
            currentFile: "file:///"+Cpp_Misc_My_Document.getFilename()+".xml" //The name of the item that you want to save
            folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
            onAccepted: {
                Cpp_Misc_My_Document.saveDocument(currentFile)
            }
        }

        Menu {
            id: filemenu
            MenuItem {
                text: qsTr("New")
                onTriggered: {
                    newDialog.open()
                }
            }
            MenuItem {
                text: qsTr("Load")
                onTriggered: {
                    loadDialog.open()
                }
            }
            MenuItem {
                text: qsTr("Save")
                onTriggered: {
                    Cpp_Misc_My_Document.saveDocument()
                }
            }
            MenuItem {
                text: qsTr("Save As")
                onTriggered: {
                    saveDialog.open()
                }
            }
        }

        Menu {
            id: createnodemenu

            MenuItem {
                text: qsTr("Create Node")
                //shortcut: StandardKey.ZoomIn
                onTriggered: createnodedialog.open()
            }
        }

        RowLayout {
            spacing: app.spacing
            anchors.fill: parent
            anchors.margins: app.spacing

            Button {
                id: filebutton
                /*anchors {
                    top: toolbar.bottom
                    left:  parent.left
                }*/

                flat: true
                icon.width: 24
                icon.height: 24
                Layout.fillHeight: true
                icon.color: "azure"
                //icon.source: "qrc:/icons/bug.svg"
                text: qsTr("File")
                onClicked: {
                    filemenu.open()
                }
            }

            Button {
                id: createnodebutton
                //anchors {
                //    top: toolbar.bottom
                //    left:  parent.left
                //}
                property string uid
                flat: true
                icon.width: 24
                icon.height: 24
                Layout.fillHeight: true
                icon.color: "azure"
                //icon.source: "qrc:/icons/bug.svg"
                text: qsTr("Create Use Case")
                onClicked: {
                    createnodemenu.open()
                }
            }

            Button {
                flat: true
                icon.width: 24
                icon.height: 24
                Layout.fillHeight: true
                icon.color: palette.text
                icon.source: "qrc:/icons/update.svg"
                text: qsTr("Check for updates")
                onClicked: {
                    Cpp_Updater.setNotifyOnFinish(Cpp_AppUpdaterUrl, true)
                    Cpp_Updater.checkForUpdates(Cpp_AppUpdaterUrl)
                }
            }

            Button {
                flat: true
                icon.width: 24
                icon.height: 24
                Layout.fillHeight: true
                icon.color: palette.text
                icon.source: "qrc:/icons/bug.svg"
                text: qsTr("Application log")
                onClicked: Cpp_Misc_Utilities.openLogFile()
            }

            Item {
                Layout.fillWidth: true
            }

            Label {
                Layout.alignment: Qt.AlignVCenter
                text: qsTr("Language") + ":"
            }

            ComboBox {
                Layout.alignment: Qt.AlignVCenter
            }
        }
    }

    function consoleoutput(nodeTitle, nodeUID, nodeParentID, nodeText, nodeXPosition, nodeYPosition) {
        console.log("model.modelData.nodeTitle: ", nodeTitle);
        console.log("model.modelData.nodeUID: ", nodeUID);
        console.log("model.modelData.nodeParentID: ", nodeParentID);
        console.log("model.modelData.nodeText: ", nodeText);
        console.log("model.modelData.nodeXPosition: ", nodeXPosition);
        console.log("model.modelData.nodeYPosition: ", nodeYPosition);
    }

    CreateNodeDialog {
        id: createnodedialog
    }

    /////// NEED TO TEST THIS FUNCTIONALTIY WHEN DOCUMENT READER FUNCTIONAITY ADDED /////////

    Repeater {
        model: Cpp_Misc_My_Document.getNodesForQml()

        //delegate: Node {
        Node {
            title: model.nodeTitle
            uid: model.nodeUID
            parentid: model.nodeParentID
            text: model.nodeText
            xposition: model.nodeXPosition
            yposition: model.nodeYPosition
        }
        Component.onCompleted: {
            consoleoutput(model.nodeTitle, model.nodeUID, model.nodeParentID, model.nodeText, model.nodeXPosition, model.nodeYPosition);
        }
    }


    NodeTreeView {
        id: nodetreeview
        width: layerviewwidth
        height: parent.height - 100
        x: 0
        y: 100

        /*anchors {
            top: parent.top - 100
            //top: createnodebutton.bottom
            left: parent.left
            bottom:  parent.middle
        }*/
    }

    Rectangle {
        anchors {
            top: parent.top
            right:  parent.right
            bottom:  parent.bottom
        }
        width: parent.width - layerviewwidth //parent.width / 1.25
        color: "azure"

        DropArea {
            anchors.fill: parent
            onEntered: drag.source.caught = true;
            onExited: drag.source.caught = false;
        }
    }

    Rectangle {
        id: droparea
        anchors {
            top: parent.top
            right:  parent.right
            bottom:  parent.bottom
        }
        width: parent.width / 1.25
        color: "azure"

        DropArea {
            anchors.fill: parent
            /*onEntered {
                drag.source.caught: true
                ld.active: !ld.active
            }*/
            onEntered: drag.source.caught = true
            onExited: drag.source.caught = false;
        }
    }
}
