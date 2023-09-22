import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

import gui

Frame {
    //width: 200
    //height: 600
    visible: true
    //title: qsTr("Tree Manipulation")

    ColumnLayout {
        anchors.fill: parent

        TreeView {
            id: treeView

            Layout.fillWidth: true
            Layout.fillHeight: true

            model: treeManipulator.sourceModel()
            selectionEnabled: true

            onCurrentIndexChanged: if(currentIndex) console.log("current index is (row=" + currentIndex.row + ", depth=" + model.depth(currentIndex) + ")")
            onCurrentDataChanged: if(currentData) console.log("current data is " + currentData)
            onCurrentItemChanged: if(currentItem) console.log("current item is " + currentItem)

        }
    }
}
