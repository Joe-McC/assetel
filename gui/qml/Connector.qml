// Connector.qml
import QtQuick 2.15
import Misc

Line {
    z: 0

    property int uid: -1 // Default value, indicating no UID assigned yet

    Connections {
        target: xmlconnector

        onXChanged: {
            console.log("Connector.qml moved to:", xmlconnector.x, xmlconnector.y);

            // Call the C++ functions with the updated positions and UID
            Cpp_Misc_My_Document.updatedConnectorStartXPos(uid, xmlconnector.x2);
            Cpp_Misc_My_Document.updatedConnectorEndXPos(uid, xmlconnector.x2);
        }

        onYChanged: {
            console.log("Connector.qml moved to:", xmlconnector.x, xmlconnector.y);

            // Call the C++ functions with the updated positions and UID
            Cpp_Misc_My_Document.updatedConnectorStartYPos(uid, xmlconnector.y1);
            Cpp_Misc_My_Document.updatedConnectorStartYPos(uid, xmlconnector.y2);
        }
    }
}
