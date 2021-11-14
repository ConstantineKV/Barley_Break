#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QTimer>
#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int turns READ turns NOTIFY nextTurn)
    Q_PROPERTY(QString time READ time NOTIFY refresh)
    Q_PROPERTY(int bestScore READ bestScore NOTIFY refreshBestScore)

    const std::chrono::duration<int> defaultTime = std::chrono::seconds(900);
public:
    GameController(QObject* parent = nullptr);
    ~GameController();
    int turns() const;
    QString time() const;
    int bestScore() const;
    void getBestScoreFromFile();
    Q_INVOKABLE void turnUp();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void saveBestScore();
signals:
    void nextTurn();
    void refresh();
    void loss();
    void refreshBestScore();
private:
    int m_turns;
    int m_bestScore;
    QTimer m_gameTimer;
    QTimer m_refreshTimer;
    QString m_time;
};

#endif // GAMECONTROLLER_H
