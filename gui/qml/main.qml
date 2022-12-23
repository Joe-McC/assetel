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
    title: qsTr("assetel")

    //
    // 'Pointer' to UI object
    //
    //property UI ui: null
    property string xmlSource: ""
    //property bool projviewer: false
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
    //Loader {
    //    id: uiloader
    //    asynchronous: true
    //    anchors.fill: parent
    //    sourceComponent: UI {
    //        anchors.fill: parent
    //        Component.onCompleted: {
    //            //app.ui = this
                //app.displayWindow()
    //        }
    //    }
    //}

    function navigate(page) {
        //loader.source =  page + ".qml";
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
            anchors.fill: parent
            //xmlSource: xmlSource
        }
    }



    Loader {
        id: loader
        anchors.fill: parent
        sourceComponent: uipage
    }

    //
    // Project Viewer content
    //
    //Loader {
    //    id: projectviwerloader
    //    anchors.fill: parent
    //    source: visible ? "ProjectViewer.qml" : ""
    //}

    //Loader {
    //    id: projectviwerloader
    //    visible: false
    //    asynchronous: true
    //    anchors.fill: parent
    //    sourceComponent: ProjectViewer {
    //        anchors.fill: parent
    //        Component.onCompleted: {
    //           //app.ui = this
    //            //app.displayWindow()
    //        }
    //    }
    //}


}
