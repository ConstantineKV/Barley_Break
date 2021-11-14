import QtQuick 2.0
import Game 1.0
import QtQuick.Controls 2.2

GridView {
    id: root
    model: GameBoardModel {
        onSuccess: {
            gameController.saveBestScore()
            popup.resultText = "You won! Want replay?"
            popup.open()
        }
    }
    interactive: true
    cellHeight: height / root.model.dimension
    cellWidth: width / root.model.dimension

    delegate: Item {
        id: _backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        visible: display != root.model.hiddenElementValue

        Tile {
            displayText: display
            width: cellWidth
            height: cellHeight

            anchors.fill: _backgroundDelegate
            anchors.margins: 5

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    gameController.turnUp()
                    root.model.move(index)
                }
            }
        }
    }

    move: Transition {
        NumberAnimation {
            properties: "x,y"
            duration: 500
        }
    }

    Popup {
        property string resultText

        id: popup
        x: parent.x + 200
        y: parent.y + 200
        width: 200
        height: 100
        modal: true
        focus: true

        //anchors.centerIn: root.anchors.centerIn
        contentItem: ReplayWindow {
            resultText: popup.resultText
            onYesAnswer: {
                model.reset()
                gameController.reset()
                popup.close()
            }
            onNoAnswer: {
                Qt.quit()
            }
        }
    }

    Connections {
        target: gameController
        onLoss: {
            popup.resultText = "You lose! Want replay?"
            popup.open()
        }
    }
}
