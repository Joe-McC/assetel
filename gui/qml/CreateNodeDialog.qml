import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


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
                               id: nodeDialogTitleInput
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
                                       nodeDialogTitleInput.selectAll()
                               }
                           }

                           Text {
                               //anchors.top: textInput.bottom
                               text: nodeDialogTitleInput.text
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
                               text: nodeDialogTextInput.text
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
                    createnodedialog.hasParent = parentCheckbox.checked
                }
                contentItem: Rectangle {
                    implicitWidth: 20
                    implicitHeight: 20
                    color: "white" // Set the checkbox background color to white
                    border.color: "black" // Set the border color to black

                    Image {
                        width: parent.width - 2
                        height: parent.height - 2
                        source: parentCheckbox.checked ? "qrc:/icons/checkmark_black.png" : ""
                        anchors.centerIn: parent
                    }
                }
            }

            ComboBox {
                id: parentComboBox
                width: 150
                enabled: parentCheckbox.checked
                model: availableParentsModel
                currentIndex: 0

                // Customize the appearance of the ComboBox
                contentItem: Rectangle {
                    width: parentComboBox.width
                    height: parentComboBox.height
                    color: "white" // Set the background color to white
                    border.color: "black" // Set the border color to black
                    Text {
                        //anchors.centerIn: parent
                        color: "black" // Set the text color to black
                        text: parentComboBox.displayText
                        horizontalAlignment: Text.AlignHLeft
                        leftPadding: 10
                    }
                }

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
                        parentComboBox.displayText = model.displayText
                    }
                    background: Rectangle {
                        implicitWidth: parent.width
                        implicitHeight: parent.height
                        opacity: enabled ? 1 : 0.3
                        border.color: createbutton.down ? "#17a81a" : "#21be2b"
                        border.width: 1
                        radius: 2
                        color: "white"  // Set the background color to white
                    }
                    Label {
                        anchors.fill: parent
                        text: parent.text
                        font.pixelSize: 16
                        color: "black" // Set the text color to black
                        horizontalAlignment: Text.AlignHLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 10
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
                    //var component;
                    var sprite;
                    var component = Qt.createComponent("Node.qml");
                    var uid;

                    // WHY HAS FOLLOWING BIT OF CODE CAUSED COMPONENT NOT READY ERROR???  POSSIBLY SOMETHING IN NODE.QML???
                    if (nodeDialogTitleInput.text !== "") {
                        // Check if a parent is selected when the checkbox is checked
                        if (createnodedialog.hasParent && createnodedialog.selectedParentId === "") {
                            // Display an error message or handle the case when no parent is selected
                            console.error("Please select a parent node.")
                        } else {
                            // Call the appropriate function to add the node
                            if (createnodedialog.hasParent) {
                                if (createnodedialog.selectedParentId !== "") {
                                    uid = qsTr(Cpp_Misc_My_Document.addNode(nodeDialogTitleInput.text.toString(), nodeDialogTextInput.text.toString(), createnodedialog.selectedParentId.toString()))
                                    console.log("child node uid: ", uid)
                                } else {
                                    console.error("Please select a parent node.")
                                }

                            } else {
                                // Add top-level node
                                uid = qsTr(Cpp_Misc_My_Document.addNode(nodeDialogTitleInput.text.toString(), nodeDialogTextInput.text.toString()))
                                console.log("top level node uid: ", uid)
                            }
                            // Retrieve the instance of ParentsModel
                            var parentsModel = availableParentsModel


                            // Add the new parent item
                            availableParentsModel.addParentItem(uid, nodeDialogTitleInput.text)

                            // Set the current index to the newly added parent item
                            parentComboBox.currentIndex = availableParentsModel.rowCount() - 1

                        }
                    }

                    var xpos = 300;
                    var ypos = 300;

//////////////////// USE IDS FROM MY Cpp_Misc_My_Document. Also, this should not happen here. Only add a new node based on what is in Cpp_Misc_My_Document (i.e. when loading an old doc or when a new node has been added_
                    sprite = component.createObject(projectviewer, {"title": nodeDialogTitleInput.text.toString(), "uid": uid.toString(), "parentid": createnodedialog.selectedParentId.toString(),  "text": nodeDialogTextInput.text.toString(), x: xpos, y: ypos})

                    Cpp_Misc_My_Document.setNewNodeXPos(uid, xpos)
                    Cpp_Misc_My_Document.setNewNodeYPos(uid, ypos)

                    parent.currentNodes.add({"name": sprite});

                    createnodedialog.close()
                    nodeDialogTitleInput.text = "" // Clear the title
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

