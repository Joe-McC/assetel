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

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            MenuSeparator {
                Layout.fillWidth: true
            }

            TextArea {
                id: txtEdit

                Layout.fillWidth: true

                placeholderText: "Write data to add..."
                placeholderTextColor: "black"
                function notEmpty() { return text !== ""}
                function clear() { text = "" }
                Text {
                    anchors.fill: parent
                    text: parent.text
                    color: "black"
                    //visible: !textEdit.text
                }
            }

            Row {
                Layout.margins: 4
                spacing: 4

                Button {
                    id: addBtn
                    text: "Add top level item"
                    enabled: txtEdit.notEmpty()

                    onClicked: {
                        treeManipulator.addTopLevelItem(txtEdit.text)
                        console.log("addChildBtn clicked");
                        txtEdit.clear()
                    }
                }

                Button {
                    id: addChildBtn
                    text: "Add child item"
                    enabled: txtEdit.notEmpty() && treeView.currentItem

                    onClicked: {
                        console.log("addChildBtn clicked");
                        treeManipulator.addItem(treeView.currentIndex, txtEdit.text)
                        txtEdit.clear()
                    }
                }

                Button {
                    id: delBtn
                    text: "Remove item"
                    enabled: treeView.currentItem

                    onClicked: {
                        treeManipulator.removeItem(treeView.currentIndex)
                    }
                }


                Button {
                    id: editBtn
                    text: "Edit item"
                    enabled: txtEdit.notEmpty() && treeView.currentItem

                    onClicked: {
                        treeManipulator.editItem(treeView.currentIndex, txtEdit.text)
                        txtEdit.clear()
                    }
                }

                Button {
                    id: clearBtn
                    text: "Clear tree"

                    onClicked:  {
                        treeManipulator.reset();
                    }
                }
            }
        }
    }
}
