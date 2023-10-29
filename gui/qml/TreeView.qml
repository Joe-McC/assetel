import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQml 2.15

Flickable {
    id: root

    implicitWidth: 400
    implicitHeight: 400
    clip: true

    property var model
    readonly property alias currentIndex: tree.selectedIndex
    readonly property alias currentItem: tree.currentItem
    property var currentData

    property alias handle: tree.handle
    property Component highlight: Rectangle {
        color: root.selectedColor
    }

    property alias selectionEnabled: tree.selectionEnabled

    property alias color: tree.color
    property alias handleColor: tree.handleColor
    property alias hoverColor: tree.hoverColor
    property alias selectedColor: tree.selectedColor
    property alias selectedItemColor: tree.selectedItemColor

    property alias rowHeight: tree.rowHeight
    property alias rowPadding: tree.rowPadding
    property alias rowSpacing: tree.rowSpacing

    property alias fontMetrics: tree.fontMetrics


    /*Rectangle {
        height: 200
        width: 200
        color: root.selectedColor
    }*/

    enum Handle {
        Triangle,
        TriangleSmall,
        TriangleOutline,
        TriangleSmallOutline,
        Chevron,
        Arrow
    }

    property int handleStyle: TreeView.Handle.Triangle

    contentHeight: tree.height
    contentWidth: width
    boundsBehavior: Flickable.StopAtBounds
    ScrollBar.vertical: ScrollBar {}

    Connections { function onCurrentIndexChanged() { if(currentIndex) currentData = model.data(currentIndex) }  }

    TreeViewItem {
        id: tree

        model: root.model
        parentIndex: model.rootIndex()
        childCount: model.rowCount(parentIndex)

        itemLeftPadding: 0
        color: root.color
        handleColor: "green" //root.handleColor
        hoverColor: root.hoverColor
        selectedColor: root.selectedColor
        selectedItemColor: "red" //root.selectedItemColor
        defaultIndicator: indicatorToString(handleStyle)
        z: 1

        Connections {
           target: root.model
           ignoreUnknownSignals: true
           function onLayoutChanged() {
               tree.childCount = root.model ? root.model.rowCount(tree.parentIndex) : 0
           }
        }
    }

    Loader {
        id: highlightLoader
        sourceComponent: highlight

        width: root.width
        height: root.rowHeight
        z: 0
        visible: root.selectionEnabled && tree.currentItem !== null

        Binding {
            target: highlightLoader.item
            property: "y"
            value: tree.currentItem ? tree.currentItem.mapToItem(tree, 0, 0).y + tree.anchors.topMargin : 0
            when: highlightLoader.status === Loader.Ready
        }
    }

    function indicatorToString(handle){
        switch (handle){
            case TreeView.Handle.Triangle: return "▶";
            case TreeView.Handle.TriangleSmall: return "►";
            case TreeView.Handle.TriangleOutline: return "▷";
            case TreeView.Handle.TriangleSmallOutline: return "⊳";
            case TreeView.Handle.Chevron: return "❱";
            case TreeView.Handle.Arrow: return "➤";
            default: return "▶";
        }
    }
}
