// Connector.qml
import QtQuick 2.15
import Misc

//Item {
//    id: xmlconnector

Rectangle {
    z: 0

    property var connectorList: []

    function createConnector() {
        var component = Qt.createComponent("Connector.qml");
        if (component.status === Component.Ready) {
            var connectorItem = component.createObject(parent, {});

            if (connectorItem !== null) {
                // Optional: Set additional properties or connect signals here
                connectorItem.x = 500;
                connectorItem.y = 500;
                connectorList.push(connectorItem);
                uid = qsTr(Cpp_Misc_My_Document.addConnector());
            } else {
                console.error("Error creating Connector.qml component");
            }
        } else {
            console.error("Error loading Connector.qml component");
        }
    }

    property var nodeList: []

    function createNode(title, uid, parentId, text, xpos, ypos) {
        console.log("createNode title: ", title)
        console.log("createNode uid: ", uid)
        console.log("createNode parentId: ", parentId)
        console.log("createNode text: ", text)
        console.log("createNode xpos: ", xpos)
        console.log("createNode ypos: ", ypos)

        var xPosition = parseInt(xpos);
        var yPosition = parseInt(ypos);

        var component = Qt.createComponent("Node.qml");
        if (component.status === Component.Ready) {
            var sprite = component.createObject(projectviewer, {
                "title": title,
                "uid": uid.toString(),
                "parentid": parentId.toString(),
                "text": text,
                "x": xPosition,
                "y": yPosition
            });

            if (sprite === null) {
                console.error("Error creating object");
            } else {
                // Add the created node to the list
                nodeList.push(sprite);
                availableParentsModel.addParentItem(uid, title);
                console.info("ProjectViewer createNode")
            }
        } else {
            console.error("Error loading component:", component.errorString());
        }
    }

    function deleteNodes(newUID) {
        // Iterate through the list of nodes and delete nodes with matching UIDs
        for (var j = 0; j < nodeList.length; ++j) {
            if (nodeList[j].uid === newUID) {
                nodeList[j].destroy();
                nodeList.splice(j, 1); // Remove the deleted node from the list
                j--; // Adjust the index after removing an element
            }
        }
    }

}
