import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: popupWindow
    width: 200
    height: 100
    property string resultText

    signal yesAnswer
    signal noAnswer

    Text {
        id: popupText
        x: 25
        y: 10
        width: 50
        height: 20

        text: resultText
    }
    Button {
        x: 25
        y: 40
        width: 40
        height: 25
        anchors.top: popupText.anchors.bottom
        anchors.topMargin: 40
        text: "Yes"
        onClicked: yesAnswer()
    }

    Button {
        x: 105
        y: 40
        width: 40
        height: 25
        anchors.top: popupText.anchors.bottom
        anchors.topMargin: 40
        text: "No"
        onClicked: noAnswer()
    }
}
