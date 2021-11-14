import QtQuick 2.12
import QtQuick.Window 2.12
import Game 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Barley Break")

    Rectangle {
        id: gameField
        border.color: Color.Black
        border.width: 1
        width: parent.width - gamePanel.width
        height: parent.height
        anchors.right: gamePanel.left
        GameBoard {
            anchors.fill: parent
        }
    }
    Rectangle {
        id: gamePanel
        width: 150
        height: parent.height
        border.color: Color.Black
        border.width: 3
        anchors.right: parent.right

        GameInfoField {
            id: turns
            anchors.left: parent.left
            anchors.leftMargin: 10
            labelText: "Turns:"
            fieldText: gameController.turns
        }
        GameInfoField {
            id: timer
            anchors.top: turns.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            labelText: "Timer:"
            fieldText: gameController.time
        }
        GameInfoField {
            id: bestScore
            anchors.top: timer.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            labelText: "Best Score:"
            fieldText: gameController.bestScore
        }
    }
}
