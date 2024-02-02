// Connector.qml
import QtQuick 2.15
import Misc

Rectangle {
    z: 0

    property int uid: -1 // Default value, indicating no UID assigned yet

    //signal connectorMoved(int uid, int x, int y);

    Connections {
        target: xmlconnector

        onPositionChanged: {
            console.log("Connector.qml moved to:", xmlconnector.x, xmlconnector.y);

            // Call the C++ functions with the updated positions and UID
            Cpp_Misc_My_Document.updatedXPos(uid, xmlconnector.x);
            Cpp_Misc_My_Document.updatedYPos(uid, xmlconnector.y);

            // Emit a signal to notify other parts of the application
            //connectorMoved(uid, xmlconnector.x, xmlconnector.y);
        }
    }

}
