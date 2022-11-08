import QtQuick 2.15
import QtQuick.Controls 2.15


Page {
    id: folderview

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
}
