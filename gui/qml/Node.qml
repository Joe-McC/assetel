import QtQuick //2.15
import QtQuick.Controls
import QtQuick.Layouts //2.15
import QtQuick.Dialogs

Item {
    id: node
    property string title
    property string uid
    property string parentid
    property string text
    property int xposition
    property int yposition

    Rectangle {
        id: nodedialog
        //property string uid: node.uid
        //property string nodetext: node.uid
        width: 200
        height: 100
        z: mouseArea.drag.active ||  mouseArea.pressed ? 2 : 1
        x: xposition
        y:  yposition
        property point beginDrag
        property bool caught: false
        border { width:2; color: "black" }
        radius: 5
        Drag.active: mouseArea.drag.active

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Text {
                    id: titlelabel
                    text: qsTr("Title:")
                }
                Text{
                    id: titletext
                    font.family: "Helvetica"
                    font.pointSize: 12
                    text:  qsTr(node.title)
                }
            }
            RowLayout {
                Text {
                    id: uidlabel
                    text: qsTr("Node UID:")
                }
                Text{
                    id: uidtext
                    font.family: "Helvetica"
                    font.pointSize: 12
                    text:  qsTr(node.uid)
                }
            }
            RowLayout {
                Text {
                    id: parentlabel
                    text: qsTr("Node Parent:")
                }
                Text{
                    id: parenttext
                    font.family: "Helvetica"
                    font.pointSize: 12
                    text:  qsTr(node.parentid)
                }
            }
            RowLayout {
                Text {
                    id: textlabel
                    text: qsTr("Description:")
                }
                Text{
                    id: decriptiontext
                    font.family: "Helvetica"
                    font.pointSize: 12
                    text:  qsTr(node.text)
                }
            }
        }
/*
        onXChanged: {
            //if (nodedialog.isMouseOverDropArea) {
                console.log("Node.qml setNewNodeXPos: ", x)
                Cpp_Misc_My_Document.setNewNodeXPos(uid, x)
            //}
        }

        onYChanged: {
            //if (nodedialog.isMouseOverDropArea) {
                console.log("Node.qml setNewNodeYPos: ", y)
                Cpp_Misc_My_Document.setNewNodeYPos(uid, y)
            //}
        }

       MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: nodedialog

            onPressed: {
                nodedialog.beginDrag = Qt.point(nodedialog.x, nodedialog.y);
            }

            onPositionChanged: {
                //if (nodedialog.caught) {
                    //nodedialog.x += mouseArea.drag.delta.x;
                    //nodedialog.y += mouseArea.drag.delta.y;
                    //nodedialog.x += mouseArea.mouseXChanged();
                    //nodedialog.y += mouseArea.mouseXChanged();
                nodedialog.x = mouseArea.mouseX
                nodedialog.y = mouseArea.mouseY
                console.log("Node.qml onPositionChanged x: ", nodedialog.x)
                console.log("Node.qml onPositionChanged y: ", nodedialog.y)
                //}
            }

            onReleased: {
                nodedialog.x = mouseArea.mouseX
                nodedialog.y = mouseArea.mouseY
                console.log("Node.qml onReleased x: ", nodedialog.x)
                console.log("Node.qml onReleased y: ", nodedialog.y)
                // Add your logic if needed when the mouse is released
            }
        }
*/

        /*onXChanged: {
            if (mouseArea.drag.active) {
                Cpp_Misc_My_Document.setNewNodeXPos(uid, x)
            }
        }
        onYChanged: {
            if (mouseArea.drag.active) {
              Cpp_Misc_My_Document.setNewNodeYPos(uid, y)
            }
        }*/

        // Reset the position after a short delay
        Timer {
            id: timer
            interval: 1000 // Adjust the delay as needed
            onTriggered: {
                nodedialog.x = nodedialog.beginDrag.x;
                nodedialog.y = nodedialog.beginDrag.y;
                // Restore visibility
                nodedialog.visible = true;
            }
            repeat: false
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: parent

            onPressed: {
                nodedialog.beginDrag = Qt.point(nodedialog.x, nodedialog.y);
            }

            onReleased: {
                if (droparea.isMouseOverDropArea) {
                    var mousePos = mouseArea.mapToItem(projectviewer, mouse.x, mouse.y);
                    Cpp_Misc_My_Document.setNewNodeXandYPos(uid, mousePos.x, mousePos.y);
                    //Cpp_Misc_My_Document.setNewNodeYPos(uid, mousePos.y);
                    timer.start()

                    // Temporarily hide the node
                    nodedialog.visible = false;

                }
            }

            // Add ParallelAnimation
            ParallelAnimation {
                SpringAnimation {
                    target: nodedialog
                    property: "x"
                    duration: 500 // Set the duration as needed
                    spring: 2
                    damping: 0.2
                }
                SpringAnimation {
                    target: nodedialog
                    property: "y"
                    duration: 500 // Set the duration as needed
                    spring: 2
                    damping: 0.2
                }
            }
        }





        /*MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: parent
            onPressed: {
                nodedialog.beginDrag = Qt.point(nodedialog.x, nodedialog.y);
            }

            onReleased: {
                if (droparea.isMouseOverDropArea) {
                    var mousePos = drag.target.mapToItem(projectviewer, drag.target.width / 2, drag.target.height / 2);
                    Cpp_Misc_My_Document.setNewNodeXPos(uid, mousePos.x);
                    Cpp_Misc_My_Document.setNewNodeYPos(uid, mousePos.y);
                }
            }

        }
        ParallelAnimation {
            id: backAnim
            SpringAnimation { id: backAnimX; target: nodedialog; property: "x"; duration: 500; spring: 2; damping: 0.2 }
            SpringAnimation { id: backAnimY; target: nodedialog; property: "y"; duration: 500; spring: 2; damping: 0.2 }
        }*/
    }

    /*Rectangle {
        anchors {
            top: parent.top
            right:  parent.right
            bottom:  parent.bottom
        }
        width: parent.width / 2
        color: "gold"
        DropArea {
            anchors.fill: parent
            onEntered: drag.source.caught = true;
            onExited: drag.source.caught = false;
        }
    }*/
}
