import QtQuick //2.15
import QtQuick.Controls //2.15
import QtQuick.Layouts //2.15
import QtQuick.Dialogs

Item {
    id: node
    property string title
    property string uid
    property string parentid
    property string text

    Rectangle {
        id: nodedialog
        //property string uid: node.uid
        //property string nodetext: node.uid
        width: 200
        height: 100
        z: mouseArea.drag.active ||  mouseArea.pressed ? 2 : 1
        x: 500
        y:  100
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
