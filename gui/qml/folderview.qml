import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    visible: true
    width: 480
    height: 480
    title: qsTr("QML TreeView")

    TreeView {
        TableViewColumn {
            title: "Name"
            role: "fileName"
            width: 300
        }
        TableViewColumn {
            title: "Permissions"
            role: "filePermissions"
            width: 100
        }
        model: folderView
    }
    //TreeView {
    //    anchors.fill: parent
    //    TableViewColumn {
    //        role: "display"
    //    }
        //model: folderView
    //}
}
/*
Page {
    id: root
    ApplicationWindow {
        visible: true
        width: 480
        height: 480
        title: qsTr("QML TreeView")

        TreeView {
            anchors.fill: parent
            TableViewColumn {
                role: "display"
            }
            model: folderView
        }
    }

}*/
