// Connector.qml
import QtQuick 2.15
import Misc

//Item {
//    id: xmlconnector

Rectangle {
    z: 0

    property var connectorList: []

    property var uid

    function createConnector() {
        var component = Qt.createComponent("Connector.qml");
        if (component.status === Component.Ready) {
            uid = Cpp_Misc_My_Document.addConnector();
            var connectorItem = component.createObject(projectviewer, {
                "uid": uid // Pass the UID from Main.qml
            });

            //var connectorItem = component.createObject(parent, {});

            if (connectorItem !== null) {
                // Optional: Set additional properties or connect signals here
                connectorItem.x = 500;
                connectorItem.y = 500;
                connectorList.push(connectorItem);

            } else {
                console.error("Error creating Connector.qml component");
            }
        } else {
            console.error("Error loading Connector.qml component");
        }
    }

    function createConnectorFromLoad(connUid, startX, startY, endX, endY, startNode, endNode) {
        console.debug("************* createConnectorFromLoad ***************");
        var component = Qt.createComponent("Connector.qml");
        if (component.status === Component.Ready) {

            console.log("connUid: ", connUid)

            var connectorItem = component.createObject(projectviewer, {
                "connectorUID": connUid,
                "connectorXPositionStart": startX,
                "connectorYPositionStart": startY,
                "connectorXPositionEnd": endX,
                "connectorYPositionEnd": endY,
                "nodeStartID": startNode,
                "nodeEndID": endNode,
            });

            if (connectorItem !== null) {
                console.debug("************* set properties ***************");
                // Optional: Set additional properties or connect signals here

                connectorItem.connectorUID = connUid;
                connectorItem.connectorXPositionStart = startX;
                connectorItem.connectorYPositionStart = startY;
                connectorItem.connectorXPositionEnd = endX;
                connectorItem.connectorYPositionEnd = endY;
                connectorItem.nodeStartID = startNode;
                connectorItem.nodeEndID = endNode;

                connectorList.push(connectorItem);

            } else {
                console.error("Error creating Connector.qml component");
            }

            connectorList.push(connectorItem);

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


    function deleteConnectors(newUID) {
        // Iterate through the list of nodes and delete nodes with matching UIDs
        for (var j = 0; j < connectorList.length; ++j) {
            if (connectorList[j].uid === newUID) {
                connectorList[j].destroy();
                connectorList.splice(j, 1); // Remove the deleted node from the list
                j--; // Adjust the index after removing an element
            }
        }
    }
}
