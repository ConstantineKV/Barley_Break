#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>
#include <QList>
#include <QTimer>
#include <chrono>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT)

public:
    using Position = std::pair<size_t, size_t>;
    static constexpr size_t defaultPuzzleDimension {4};

    GameBoard(const size_t boardDimension = defaultPuzzleDimension, QObject* parent = nullptr);

signals:
    void success();

public:
    struct Tile
    {
        size_t value {};
        Tile& operator=(const size_t newValue)
        {
            value = newValue;
            return *this;
        }

        bool operator ==(const size_t other)
        {
            return other == value;
        }
    };

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Position getRawCol(size_t index) const;

    size_t dimension() const;
    size_t boardSize() const;

    Q_INVOKABLE bool move(int index);
    Q_INVOKABLE void reset();
    bool changingPosition() const;
    void setChangingPosition(bool changingPosition);
private:
    void shuffle();
    bool isPositionValid(const size_t position) const;
    bool isBoardValid() const;
    bool checkSuccess();
    void createBoard();
    std::vector<Tile> m_rawBoard;
    const size_t m_dimension;
    const size_t m_boardSize;
    bool m_changingPosition;
    int m_indexFrom;
    int m_indexTo;

};

#endif // GAMEBOARD_H
