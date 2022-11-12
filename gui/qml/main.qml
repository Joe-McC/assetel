import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id: app
    width: 640
    height: 480
    visible: true
    title: qsTr("assetel")

    //
    // 'Pointer' to UI object
    //
    property UI ui: null
    //property var folderview: null
    //property alias folderview: folderview

    //
    // Global properties
    //
    //readonly property int initWidth: 1280
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
    palette.window: app.windowBackgroundColor

    //
    // UI content
    //
    Loader {
        id: uiloader
        asynchronous: true
        anchors.fill: parent
        sourceComponent: UI {
            anchors.fill: parent
            Component.onCompleted: {
                //app.ui = this
                //app.displayWindow()
            }
        }
    }
}
