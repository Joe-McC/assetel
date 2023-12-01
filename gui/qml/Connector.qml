// Connector.qml
import QtQuick 2.15
import Misc


Rectangle {
    property point startPoint
    property point endPoint

    width: Math.abs(endPoint.x - startPoint.x)
    height: Math.abs(endPoint.y - startPoint.y)
    color: parent.color

    XMLConnector {
        id: xmlConnector
        anchors.fill: parent
    }
}
