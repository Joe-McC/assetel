import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs

Item {
    id: node
    property string uid
    property string nodetext
    //width: parent.width
    //height: parent.height

    Rectangle {
        //console.log(uid);

        id: nodedialog
        property string uid: node.uid
        property string nodetext: node.nodetext
        width: 500
        height: 280
        z: mouseArea.drag.active ||  mouseArea.pressed ? 2 : 1
        //color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
        //color: "transparent"
        x: 100
        y:  100
        property point beginDrag
        property bool caught: false
        border { width:2; color: "white" }
        radius: 5
        Drag.active: mouseArea.drag.active

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Text {
                    id: label
                    text: qsTr("Node UID:")
                }
                Text{
                    anchors.fill:parent
                    anchors.centerIn: parent
                    id: myText
                    //color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 12
                    text:  qsTr(nodedialog.uid)
                }
            }
        }


        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: parent
            onPressed: {
                nodedialog.beginDrag = Qt.point(rect.x, rect.y);
            }
            onReleased: {
                if(!nodedialog.caught) {
                    backAnimX.from = rect.x;
                    backAnimX.to = rect.beginDrag.x;
                    backAnimY.from = rect.y;
                    backAnimY.to = rect.beginDrag.y;
                    backAnim.start()
                }
            }
        }
        ParallelAnimation {
            id: backAnim
            SpringAnimation { id: backAnimX; target: nodedialog; property: "x"; duration: 500; spring: 2; damping: 0.2 }
            SpringAnimation { id: backAnimY; target: nodedialog; property: "y"; duration: 500; spring: 2; damping: 0.2 }
        }
    }

}
