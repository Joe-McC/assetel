import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs
import Qt.labs.platform
import QtQuick.Window
import QtQml.XmlListModel


Page {
    id: uimain

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
            }
        }
    }

    //
    // Background color
    //
    background: Rectangle {
        color: app.windowBackgroundColor
    }

    //
    // Image, labels & buttons
    //
    ColumnLayout {
        spacing: app.spacing
        anchors.centerIn: parent

        Image {
            source: "qrc:/icons/icon.png" //-- add logo here.
            sourceSize: Qt.size(600, 300)
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            Layout.minimumHeight: app.spacing
        }

        FileDialog {
            id: openDialog
            fileMode: FileDialog.OpenFile
            selectedNameFilter.index: 1
            nameFilters: ["Text files (*.xml)"]
            folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
            onAccepted: {
                app.xmlSource = currentFile
                Cpp_Misc_My_Document.openDocument(currentFile)
                navigate(projectviewerpage)
            }
        }

        FileDialog {
            id: createDialog
            fileMode: FileDialog.SaveFile
            nameFilters: openDialog.nameFilters
            folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
            //onAccepted: Cpp_Misc_My_Document.openDocument(currentFile)
            onAccepted: {
                app.xmlSource = currentFile
                Cpp_Misc_My_Document.openDocument(currentFile)
                navigate(projectviewerpage)
            }
        }

        Button {
            icon.color: palette.text
            Layout.minimumWidth: 156
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Create New Project")
            onClicked:{
                createDialog.open()
            }
        }
        Button {
            icon.color: palette.text
            Layout.minimumWidth: 156
            Layout.alignment: Qt.AlignHCenter
            icon.source: "qrc:/icons/openfolder.png"
            text: qsTr("Open Existing Project")
            onClicked: openDialog.open()
        }

        Item {
            Layout.minimumHeight: app.spacing
        }

        Button {
            icon.color: palette.text
            Layout.minimumWidth: 156
            Layout.alignment: Qt.AlignHCenter
            icon.source: "qrc:/icons/close.svg"
            text: qsTr("Close")
            onClicked: app.close()
        }

        Button {
            icon.color: palette.text
            Layout.minimumWidth: 156
            Layout.alignment: Qt.AlignHCenter
            icon.source: "qrc:/icons/website.svg"
            text: qsTr("Visit website")
            onClicked: Qt.openUrlExternally(Cpp_AppOrganizationDomain)
        }
    }
}


