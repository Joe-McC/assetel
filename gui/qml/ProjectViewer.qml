import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs
import Qt.labs.platform
import QtQuick.Window



Page {
    id: projectviewer
    //
    // Toolbar with buttons
    //
    property int layerviewwidth: 300

    header: ToolBar {
        id: toolbar
        height: 48
        z: 1

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
                navigate(projectviewerpage)
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

                projectviewerpage.active = !projectviewerpage.active

                projectviewerpage.active = !projectviewerpage.active
                Cpp_Misc_My_Document.openDocument(currentFile)
            }
        }

        FileDialog {
            id: saveDialog
            fileMode: FileDialog.SaveFile
            selectedNameFilter.index: 1
            currentFile: "file:///"+Cpp_Misc_My_Document.getFilename()+".xml" //The name of the item that you want to save
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
            MenuItem {
                text: qsTr("Close")
                onTriggered: {
                    Cpp_Misc_My_Document.closeDocument()
                    nodeListModel.modelCleared = true

                    console.log("Model is cleared. Deleting all nodes.");
                    // Delete all nodes in the nodeList
                    for (var i = 0; i < nodeList.length; ++i) {
                        nodeList[i].destroy();
                    }
                    nodeList = []; // Clear the nodeList
                }
            }
        }

        Menu {
            id: projectmenu
            MenuItem {
                text: qsTr("Add Connector")
                onTriggered: {
                    drawingpane.createConnector()
                }
            }
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
                id: projectbutton
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
                    projectmenu.open()
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

    DrawingPane {
        id: drawingpane
        width: parent.width//Math.abs(endPoint.x - startPoint.x)
        height: parent.height - 48//Math.abs(endPoint.y - startPoint.y)
        anchors.left: parent.left//Math.abs(endPoint.x - startPoint.x)
        anchors.bottom: parent.bottom//Math.abs(endPoint.y - startPoint.y)

        property int mouseX: 0
        property int mouseY: 0
    }


    // Issues:
    //1.data now being loaded. Connectors not yet being drawn.
    //2.when both nodes and connectors are being loaded, the connectors aren't being read in the xmlprocessor.


    Repeater {
        model: connectorListModel

        delegate: Connector {
            property bool clearConnectorsCompleted: false

            Component.onCompleted: {
                // Iterate over the model data and access it here
                console.log("model.data 2: ", model.connectorID)
                drawingpane.deleteConnectors(model.connectorID);
                drawingpane.createConnectorFromLoad(model.connectorID, model.connectorStartPosX, model.connectorStartPosY, model.connectorEndPosX, model.connectorEndPosY, model.nodeStartID, model.nodeEndID);
            }
        }
    }


    Repeater {
        model: nodeListModel
        delegate: Node {
            property bool clearNodesCompleted: false

            Component.onCompleted: {
                console.log("model.data 1: ", model.nodeUID)
                drawingpane.deleteNodes(model.nodeUID);
                drawingpane.createNode(model.nodeTitle, model.nodeUID, model.nodeParentID, model.nodeText, model.nodeXPosition, model.nodeYPosition);
            }
        }
    }


    /*Repeater {
        model: connectorListModel
        delegate: Connector {
            property bool clearConnectorsCompleted: false


            ///////////////////// data() isn't being called /////////////////////
            Component.onCompleted: {
                drawingpane.deleteConnectors(model.connectorUID);
                drawingpane.createConnectorFromLoad(connectorListModel.connectorID, connectorListModel.connectorStartPosX, connectorListModel.connectorStartPosY, connectorListModel.connectorEndPosX, connectorListModel.connectorEndPosY, connectorListModel.nodeStartID, connectorListModel.nodeEndID);
                for (var i = 0; i < connectorListModel.count; ++i) {
                    var modelData = connectorListModel.get(i);
                    console.log("model.connectorUID: ", modelData.connectorID)
                    console.log("model.connectorStartPositionX: ", modelData.connectorStartPosX)
                    console.log("model.connectorStartPositionY: ", modelData.connectorStartPosY)
                    console.log("model.connectorEndPositionX: ", modelData.connectorEndPosX)
                    console.log("model.connectorEndPositionY: ", modelData.connectorEndPosY)
                    console.log("model.nodeStartID: ", modelData.nodeStartID)
                    console.log("model.nodeEndID: ", modelData.nodeEndID)
                    var connectorComponent = Qt.createComponent("Connector.qml");
                    if (connectorComponent.status === Component.Ready) {
                        var connectorItem = connectorComponent.createObject(connectorRepeater, {
                            "connectorUID": modelData.connectorUID,
                            "connectorStartPositionX": modelData.connectorStartPositionX,
                            "connectorStartPositionY": modelData.connectorStartPositionY,
                            "connectorEndPositionX": modelData.connectorEndPositionX,
                            "connectorEndPositionY": modelData.connectorEndPositionY,
                            "nodeStartID": modelData.nodeStartID,
                            "nodeEndID": modelData.nodeEndID
                        });

                        if (connectorItem === null) {
                            console.error("Error creating Connector component:", connectorComponent.errorString());
                        }
                    } else {
                        console.error("Error loading Connector.qml:", connectorComponent.errorString());
                    }
                }
            }
        }
    }
*/
    NodeTreeView {
        id: nodetreeview
        width: layerviewwidth
        height: parent.height - 100
        x: 0
        y: 100
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

        property bool isMouseOverDropArea: false // New property to track mouse over

        anchors {
            top: parent.top
            right:  parent.right
            bottom:  parent.bottom
        }
        width: parent.width / 1.25
        color: "azure"

        DropArea {
            anchors.fill: parent

            onEntered: {
                // Handle the logic when a node is entered into the drop area
                droparea.isMouseOverDropArea = true;
            }

            onExited: {
                // Handle the logic when a node is exited from the drop area
                droparea.isMouseOverDropArea = false;
            }
        }

    }
}
