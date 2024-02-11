import QtQuick 2.15
import QtQuick.Shapes 1.15
import Misc

XMLConnector {
    id: xmlconnector
    anchors.fill: parent

    property int uid: -1 // Default value, indicating no UID assigned yet

    onXChanged: {
        // Call the C++ functions with the updated positions and UID
        Cpp_Misc_My_Document.updatedConnectorStartXPos(uid, xmlconnector.connectorXPositionStart);
        Cpp_Misc_My_Document.updatedConnectorEndXPos(uid, xmlconnector.connectorXPositionEnd);
    }

    onYChanged: {
        // Call the C++ functions with the updated positions and UID
        Cpp_Misc_My_Document.updatedConnectorStartYPos(uid, xmlconnector.connectorYPositionStart);
        Cpp_Misc_My_Document.updatedConnectorEndYPos(uid, xmlconnector.connectorYPositionEnd);
    }
}
