// ConnectorItem.qml
import QtQuick 2.15
import Misc

Item {
    property int xposition
    property int yposition
    width: 400
    height: 400

    XMLConnector {
        anchors.fill: parent
    }
}
