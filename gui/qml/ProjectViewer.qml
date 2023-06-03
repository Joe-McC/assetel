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
                /*onTriggered: {
                    var component;
                    var sprite;
                    component = Qt.createComponent("Node.qml");
                    sprite = component.createObject(projectviewer, {"uid": qsTr(Cpp_Misc_My_Document.addNode())})
                    onRejected: console.log("Cancel clicked")
                }*/
            }

            /*MenuItem {
                text: qsTr("Zoom Out")
                //shortcut: StandardKey.ZoomOut
                onTriggered: zoomOut()
            }*/
        }



        /*Dialog {
            id: createnodedialog
            title: "Create Node"
            modal: true
            standardButtons: Dialog.Ok | Dialog.Cancel

            onAccepted: {
                var component;
                var sprite;
                component = Qt.createComponent("Node.qml");
                sprite = component.createObject(projectviewer, {"uid": qsTr(Cpp_Misc_My_Document.addNode())})
                onRejected: console.log("Cancel clicked")
            }
            onRejected: console.log("Cancel clicked")
        }*/

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
                /*Rectangle {
                    x: 200
                    y: 1000
                    color: "black"

                    /*ScrollView {
                        id: textinputview
                        //anchors.fill: parent
                    }
                }*/
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

                            TextArea {
                                id: textInput
                                wrapMode: TextArea.Wrap
                                placeholderText: "Enter your text here..."
                                width: parent.width
                                height: contentHeight
                                color: "black" // Set text color to white for contrast
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
                        sprite = component.createObject(projectviewer, {"uid": qsTr(Cpp_Misc_My_Document.addNode())})
                        createnodedialog.close()
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



    /*TreeView {
        anchors {
            //top: parent.top
            left: parent.left
            bottom:  parent.bottom
        }
        width: parent.width - droparea.width
        height: parent.height / 1.5
        // The model needs to be a QAbstractItemModel
        model: Cpp_TreeView_Model

        delegate: Item {
            id: treeDelegate

            implicitWidth: padding + label.x + label.implicitWidth + padding
            implicitHeight: label.implicitHeight * 1.5

            readonly property real indent: 20
            readonly property real padding: 5

            // Assigned to by TreeView:
            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property int hasChildren
            required property int depth

            TapHandler {
                onTapped: treeView.toggleExpanded(row)
            }

            Text {
                id: indicator
                visible: treeDelegate.isTreeNode && treeDelegate.hasChildren
                x: padding + (treeDelegate.depth * treeDelegate.indent)
                anchors.verticalCenter: label.verticalCenter
                text: "▸"
                rotation: treeDelegate.expanded ? 90 : 0
            }

            Text {
                id: label
                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1) * treeDelegate.indent : 0)
                width: treeDelegate.width - treeDelegate.padding - x
                clip: true
                text: model.display
            }
        }
    }*/


    /*Rectangle {
        anchors.left: parent
        color: "#e6dddd"
        border.color: "#00bb7b7b"
        //fillWidth: true
        //minimumWidth: 50
        //preferredWidth: 100
        width:100
        height: 150
        //maximumWidth: 300
        //minimumHeight: 150
        Text {
            anchors.centerIn: parent
            text: parent.width + 'x' + parent.height
        }
    }*/
    //XMLWriter{
    //    id: xmlWriter
    //}




    // ---------------------------------------------------------------------------------------------------
    // XML Section

    // WRITE TO XML HERE ALSO

    /*XmlListModel {
        id: xmlModel
        source: app.xmlSource
        query: "/documents/document"
        // ...
        XmlListModelRole {
            name: "pages"
            elementName: "info/num_pages"
        }
    }*/

    /*Rectangle {
        anchors.centerIn: parent
        color: "#e6dddd"
        border.color: "#00bb7b7b"
        //fillWidth: true
        //minimumWidth: 50
        //preferredWidth: 100
        width:100
        height: 150
        //maximumWidth: 300
        //minimumHeight: 150
        ListView {
            anchors.fill: parent
            model: xmlModel
            // delegate:  Text { text: " num pages= " + pages }
            delegate:  Text { text: myXMLDocument.name }
        }
    }*/

    //Node {
        //anchors.centerIn: parent

    //}



    /*XMLDocument {
        id: myXMLDocument
        name: "test document"
    }*/

    // Test
    /*ListView {
        anchors.fill: parent
        model: xmlModel
        delegate:  Text { text: " num pages= " + pages }
    }*/

}
