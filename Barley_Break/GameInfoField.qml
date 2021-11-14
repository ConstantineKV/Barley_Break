import QtQuick 2.0

Item {
    property string labelText: "0"
    property string fieldText

    height: 50
    width: 200
    Text{
        anchors.top: parent.top
        anchors.topMargin: 10

        id: label
        height: 15
        width: 70
        font.italic: false
        font.pointSize: 10
        text: labelText

        color: color.black
    }

    Rectangle{
        height: 30
        width: 100
        anchors.top: label.bottom
        anchors.topMargin: 5
        border.color: color.black
        border.width: 1
        Text {
            id: field
            text: fieldText
            font.italic: false
            font.pointSize: 12
            anchors.centerIn: parent
            color: color.black
        }
    }
}
