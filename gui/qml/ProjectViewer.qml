import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs
import Qt.labs.platform
import QtQuick.Window
import QtQml.XmlListModel
//import gui //false positive error: see https://stackoverflow.com/questions/71182775/how-to-register-qobject-class-in-cmake-with-qt-add-qml-module


Page {
    id: projectviewer
    //
    // Toolbar with buttons
    //
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
                id: createnodebutton
                anchors {
                    top: toolbar.bottom
                    left:  parent.left
                }
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


    Popup {
        id: createnodedialog
        palette.text: "black"
        anchors.centerIn: parent

        property bool hasParent: false // Add the hasParent property here
        // Add the selectedParentId property
        property string selectedParentId: ""

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Text {
                    id: titlelabel
                    text: qsTr("Node Title:")
                }

                Item {
                    id: addNodeDialogTitle
                    width: 300
                    height: 50

                    ScrollView {
                        anchors.fill: parent

                        Rectangle {
                            color: "transparent"
                            border.color: "black"
                            border.width: 2
                            radius: 5
                            anchors.fill: parent

                            FocusScope {
                               anchors.fill: parent

                               TextArea {
                                   id: nodeDialogTextInput
                                   inputMethodHints: Qt.ImhSensitiveData
                                   wrapMode: TextArea.Wrap
                                   placeholderText: "Enter your text here..."
                                   width: parent.width
                                   height: contentHeight
                                   color: "white"
                                   background: Rectangle {
                                       color: "transparent"
                                   }

                                   onActiveFocusChanged: {
                                       if (activeFocus)
                                           nodeDialogTextInput.selectAll()
                                   }
                               }

                               Text {
                                   //anchors.top: textInput.bottom
                                   text: nodeDialogTextInput.text
                                   leftPadding: 10
                                   topPadding: 5
                               }
                           }
                        }
                    }
                }
            }

            RowLayout {
                Text {
                    id: label
                    text: qsTr("Node Text:")
                }

                Item {
                    id: addNodeDialogTextBox
                    width: 300
                    height: 200

                    ScrollView {
                        anchors.fill: parent

                        Rectangle {
                            color: "transparent"
                            border.color: "black"
                            border.width: 2
                            radius: 5
                            anchors.fill: parent

                            FocusScope {
                               anchors.fill: parent

                               TextArea {
                                   id: nodeDialogTileTextInput
                                   inputMethodHints: Qt.ImhSensitiveData
                                   wrapMode: TextArea.Wrap
                                   placeholderText: "Enter your text here..."
                                   width: parent.width
                                   height: contentHeight
                                   color: "white"
                                   background: Rectangle {
                                       color: "transparent"
                                   }

                                   onActiveFocusChanged: {
                                       if (activeFocus)
                                           nodeDialogTileTextInput.selectAll()
                                   }
                               }

                               Text {

                                   text: nodeDialogTileTextInput.text
                                   leftPadding: 10
                                   topPadding: 5
                               }
                           }
                        }
                    }
                }
            }

            Row {
                CheckBox {
                    id: parentCheckbox
                    text: "Has Parent"
                    onCheckedChanged: {
                        createnodedialog.hasParent = checked
                    }
                }

                ComboBox {
                    id: parentComboBox
                    width: 150
                    enabled: parentCheckbox.checked
                    model: availableParentsModel
                    currentIndex: 0
                    onAccepted: {
                        if (currentIndex >= 0 && currentIndex < availableParentsModel.count) {
                            // Use currentText property to get the selected parent
                            createnodedialog.selectedParentId = parentComboBox.currentText;
                        } else {
                            createnodedialog.selectedParentId = "";
                        }
                    }

                   delegate: Button {
                        width: parentComboBox.width
                        height: 30
                        text: model.displayText // Access the displayText property
                        onClicked: {
                            parentComboBox.currentIndex = index;
                            createnodedialog.selectedParentId = model.nodeId;
                        }
                    }
                }
            }

            RowLayout {            
                Button {
                    id: createbutton
                    property string uid
                    flat: true
                    icon.width: 24
                    icon.height: 24
                    Layout.fillHeight: true
                    icon.color: "azure"
                    text: qsTr("Create")
                    onClicked: {
                        var component;
                        var sprite;
                        component = Qt.createComponent("Node.qml");
                        var uid;

                        // WHY HAS FOLLOWING BIT OF CODE CAUSED COMPONENT NOT READY ERROR???  POSSIBLY SOMETHING IN NODE.QML???
                        if (nodeDialogTextInput.text !== "") {
                            // Check if a parent is selected when the checkbox is checked
                            if (createnodedialog.hasParent && createnodedialog.selectedParentId === "") {
                                // Display an error message or handle the case when no parent is selected
                                console.error("Please select a parent node.")
                            } else {
                                // Call the appropriate function to add the node
                                if (createnodedialog.hasParent) {
                                    if (createnodedialog.selectedParentId !== "") {
                                        uid = qsTr(Cpp_Misc_My_Document.addNode(nodeDialogTextInput.text.toString(), createnodedialog.selectedParentId.toString()))
                                        console.log("child node uid: ", uid)
                                    } else {
                                        console.error("Please select a parent node.")
                                    }

                                } else {
                                    // Add top-level node
                                    uid = qsTr(Cpp_Misc_My_Document.addNode(nodeDialogTextInput.text.toString()))
                                    console.log("top level node uid: ", uid)
                                }
                                // Retrieve the instance of ParentsModel
                                var parentsModel = availableParentsModel

                                // Create a new parent item
                                var newNodeId = uid
                                var newDisplayText = nodeDialogTextInput.text

                                // Add the new parent item
                                availableParentsModel.addParentItem(newNodeId, newDisplayText)

                                // Set the current index to the newly added parent item
                                parentComboBox.currentIndex = availableParentsModel.rowCount() - 1
                                // Close the dialog
                                //createnodedialog.close()
                            }
                        }


                        sprite = component.createObject(projectviewer, {"uid": uid})
                        //sprite.nodetext = textInput.text;

                        createnodedialog.close()
                        nodeDialogTextInput.text = "" // Clear the text
                    }
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        border.color: createbutton.down ? "#17a81a" : "#21be2b"
                        border.width: 1
                        radius: 2
                        color: "black"  // I update background color by this
                    }
                }
                Button {
                    id: cancelbutton
                    property string uid
                    flat: true
                    icon.width: 24
                    icon.height: 24
                    Layout.fillHeight: true
                    icon.color: "azure"
                    text: qsTr("Cancel")
                    onClicked: {
                        createnodedialog.close()
                        nodeDialogTextInput.text = "" // Clear the text
                    }
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        border.color: createbutton.down ? "#17a81a" : "#21be2b"
                        border.width: 1
                        radius: 2
                        color: "black"  // I update background color by this
                    }
                }
            }
        }
    }

    NodeTreeView {
        id: nodetreeview
        //height: parent.height
        //width: 600
        width: 200
        height: 800
        anchors {
            top: parent.top - 100
            //top: createnodebutton.bottom
            left: parent.left
            bottom:  parent.middle
        }
    }

    Rectangle {
        anchors {
            top: parent.top
            right:  parent.right
            bottom:  parent.bottom
        }
        width: parent - nodetreeview.width //parent.width / 1.25
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
