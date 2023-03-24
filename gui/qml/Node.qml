import QtQuick

Item {
    property string uid
    width: parent.width
    height: parent.height

    Rectangle {
        id: rect
        width: 50
        height: 28
        z: mouseArea.drag.active ||  mouseArea.pressed ? 2 : 1
        //color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
        color: "transparent"
        x: 100
        y:  100
        property point beginDrag
        property bool caught: false
        border { width:2; color: "white" }
        radius: 5
        Drag.active: mouseArea.drag.active
        //Text: "uid"    -- set this via uid which is determined by C++ function from projectviewer call

        //TextInput didn't seem to work without an addition Rectangle component in the level above
        //- possibly to do with the MouseArea and TextInput functionility clashing
        /*Rectangle {
            property alias text: input.text
            anchors.centerIn: parent
            width: 180
            height: 28
            color: "azure"
            border.color: "black"

            TextInput {
                id: input
                color: "#151515"; selectionColor: "green"
                font.pixelSize: 16; font.bold: true
                width: parent.width-16
                maximumLength: 32
                anchors.centerIn: parent
                focus: true
            }
        }*/
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: parent
            onPressed: {
                rect.beginDrag = Qt.point(rect.x, rect.y);
            }
            onReleased: {
                if(!rect.caught) {
                    backAnimX.from = rect.x;
                    backAnimX.to = beginDrag.x;
                    backAnimY.from = rect.y;
                    backAnimY.to = beginDrag.y;
                    backAnim.start()
                }
            }
        }
        ParallelAnimation {
            id: backAnim
            SpringAnimation { id: backAnimX; target: rect; property: "x"; duration: 500; spring: 2; damping: 0.2 }
            SpringAnimation { id: backAnimY; target: rect; property: "y"; duration: 500; spring: 2; damping: 0.2 }
        }
    }
}
