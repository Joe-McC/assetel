import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs
import Qt.labs.platform
import QtQuick.Window
import QtQml.XmlListModel
import gui //false positive error: see https://stackoverflow.com/questions/71182775/how-to-register-qobject-class-in-cmake-with-qt-add-qml-module


Page {
    id: root
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
            delegate:  Text { text: " num pages= " + pages }
        }
    }

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
