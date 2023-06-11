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

            Text {
                text: "TEST"
            }
            Text {
                text: app.xmlSource
            }

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
                //model: Cpp_Misc_Translator.availableLanguages
                //onCurrentIndexChanged: Cpp_Misc_Translator.setLanguage(currentIndex)
            }
        }
    }


    Popup {
        id: createnodedialog
        palette.text: "black"
        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Text {
                    id: label
                    text: qsTr("Node:")
                }

                Item {
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
                                   id: textInput
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
                                           textInput.selectAll()
                                   }
                               }

                               Text {
                                   //anchors.top: textInput.bottom
                                   text: textInput.text
                                   leftPadding: 10
                                   topPadding: 5
                               }
                           }
                        }
                    }
                }
            }

            RowLayout {
                Button {
                    id: okbutton
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
                        //sprite = component.createObject(projectviewer, {"uid": qsTr(Cpp_Misc_My_Document.addNode())})
                        sprite = component.createObject(projectviewer, {"uid": qsTr(Cpp_Misc_My_Document.addNode(textInput.text))})
                        createnodedialog.close()
                        textInput.text = "" // Clear the text
                    }
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        border.color: okbutton.down ? "#17a81a" : "#21be2b"
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
                        textInput.text = "" // Clear the text
                    }
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        border.color: okbutton.down ? "#17a81a" : "#21be2b"
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
