import QtQuick 2.15
import QtQuick.Shapes 1.15
import Misc

XMLConnector {
    id: xmlconnector
    anchors.fill: parent

    property string uid // Default value, indicating no UID assigned yet

    // Signal handlers for property changes
    onConnectorXPositionStartChanged: {
        Cpp_Misc_My_Document.updatedConnectorStartXPos(uid, xmlconnector.connectorXPositionStart)
    }
    onConnectorYPositionStartChanged: {
        Cpp_Misc_My_Document.updatedConnectorStartYPos(uid, xmlconnector.connectorYPositionStart)
    }
    onConnectorXPositionEndChanged: {
        Cpp_Misc_My_Document.updatedConnectorEndXPos(uid, xmlconnector.connectorXPositionEnd)
    }
    onConnectorYPositionEndChanged: {
        Cpp_Misc_My_Document.updatedConnectorEndYPos(uid, xmlconnector.connectorYPositionEnd)
    }

    // Callbacks for manual property changes
    onXChanged: {
        Cpp_Misc_My_Document.updatedConnectorStartXPos(uid, xmlconnector.connectorXPositionStart);
        Cpp_Misc_My_Document.updatedConnectorEndXPos(uid, xmlconnector.connectorXPositionEnd);
    }

    onYChanged: {
        Cpp_Misc_My_Document.updatedConnectorStartYPos(uid, xmlconnector.connectorYPositionStart);
        Cpp_Misc_My_Document.updatedConnectorEndYPos(uid, xmlconnector.connectorYPositionEnd);
    }
}
