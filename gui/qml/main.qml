import QtQuick //2.15
import QtQuick.Window //2.15
import QtQuick.Controls //2.15
import QtQuick.Dialogs
import QtQuick.Layouts


ApplicationWindow {
    id: app
    width: 2560
    height: 1600
    visible: true
    visibility: "Maximized"
    title: qsTr("assetel")

    //
    // 'Pointer' to UI object
    //
    //property UI ui: null
    property string xmlSource: ""
    property string xmlContent: ""

    //
    // Global properties
    //
    readonly property int spacing: 8
    readonly property color foregroundColor: "#ffffff"
    readonly property color windowBackgroundColor: "#121920"
    readonly property string monoFont: {
        switch (Qt.platform.os) {
        case "osx":
            return "Menlo"
        case "windows":
            return "Consolas"
        default:
            return "Monospace"
        }
    }

    //
    // Theme options
    //
    palette.text: app.foregroundColor
    palette.buttonText: app.foregroundColor
    palette.windowText: app.foregroundColor
    palette.window: "white"

    function navigate(page) {
        loader.sourceComponent = page;
    }

    Component {
        id: uipage
        UI {
            id: ui
            anchors.fill: parent
        }
    }

    Component {
        id: projectviewerpage
        ProjectViewer {
            id: projectviewer
            //anchors.fill: parent
            //xmlSource: xmlSource
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
        sourceComponent: uipage
    }
}
