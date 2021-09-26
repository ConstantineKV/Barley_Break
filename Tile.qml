import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""
    readonly property alias internalText: _firstText

    color: "lightgreen"
    border.color: "black"
    border.width: 1
    radius: 5
    Text {
        id: _firstText
        anchors.centerIn: root

        text: displayText
        font {
            pointSize: Math.min(root.width, root.height) / 3
            bold: true
        }
    }

}

