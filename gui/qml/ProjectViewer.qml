import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs
import Qt.labs.platform
import QtQuick.Window
import QtQml.XmlListModel
import gui //false positive error: see https://stackoverflow.com/questions/71182775/how-to-register-qobject-class-in-cmake-with-qt-add-qml-module


Page {
    id: projectviewer
    //
    // Toolbar with buttons
    //
    header: ToolBar {
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
        RowLayout {
            spacing: app.spacing
            anchors.fill: parent
            anchors.margins: app.spacing

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

    Rectangle {
        anchors {
            top: parent.top
            right:  parent.right
            bottom:  parent.bottom
        }
        width: parent.width / 1.25
        color: "azure"

        DropArea {
            anchors.fill: parent
            onEntered: drag.source.caught = true;
            onExited: drag.source.caught = false;
        }
    }


    Button {
        property string uid
        flat: true
        icon.width: 24
        icon.height: 24
        Layout.fillHeight: true
        icon.color: "azure"
        //icon.source: "qrc:/icons/bug.svg"
        text: qsTr("Create Use Case")
        onClicked: {

            var component;
            var sprite;
            component = Qt.createComponent("Node.qml");
            //uid: qsTr(Cpp_Misc_My_Document.addNode())
            //console.log("uid: " + uid + ".end");
            //console.log("uid2: " + qsTr(Cpp_Misc_My_Document.addNode()) + ".end");
            //sprite = component.createObject(projectviewer, {"x": 100, "y": 100})


            sprite = component.createObject(projectviewer, {"uid": qsTr(Cpp_Misc_My_Document.addNode())})
            //sprite = component.createObject(projectviewer)
        }

    }






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

    XmlListModel {
        id: xmlModel
        source: app.xmlSource
        query: "/documents/document"
        // ...
        XmlListModelRole {
            name: "pages"
            elementName: "info/num_pages"
        }
    }

    Rectangle {
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
    }

    //Node {
        //anchors.centerIn: parent

    //}



    XMLDocument {
        id: myXMLDocument
        name: "test document"
    }

    // Test
    /*ListView {
        anchors.fill: parent
        model: xmlModel
        delegate:  Text { text: " num pages= " + pages }
    }*/

}
