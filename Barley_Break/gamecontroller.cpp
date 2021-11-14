#include <gamecontroller.h>
#include <QFile>
#include <QTextStream>

GameController::GameController(QObject* parent) : QObject(parent), m_turns(0)
{
    getBestScoreFromFile();

    m_gameTimer.setInterval(std::chrono::duration_cast<std::chrono::milliseconds>(defaultTime));
    m_gameTimer.setSingleShot(true);

    m_refreshTimer.setInterval(500);
    m_refreshTimer.setSingleShot(false);
    m_refreshTimer.start();
    connect(&m_refreshTimer,SIGNAL(timeout()), this, SIGNAL(refresh()));
    connect(&m_gameTimer,SIGNAL(timeout()), this, SIGNAL(loss()));
}

void GameController::getBestScoreFromFile()
{
    QFile file("bestScore.txt");

    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QString line;
        QTextStream in(&file);
        if (!in.atEnd())
            line = in.readLine();
        m_bestScore = line.toInt();
        file.close();
    }
    else
        m_bestScore = 0;
    emit refreshBestScore();
}

int GameController::bestScore() const
{
    return m_bestScore;
}

GameController::~GameController()
{

}

int GameController::turns() const
{
    return m_turns;
}

QString GameController::time() const
{
    QString outputTime;

    QString minutes;
    QString seconds;
    if (m_gameTimer.remainingTime()/1000/60 > 9)
        minutes = QString::number(m_gameTimer.remainingTime()/1000/60);
    else
        minutes = "0" + QString::number(m_gameTimer.remainingTime()/1000/60);

    if (m_gameTimer.remainingTime() / 1000 % 60 > 9)
        seconds = QString::number(m_gameTimer.remainingTime() / 1000 % 60);
    else
        seconds = "0" + QString::number(m_gameTimer.remainingTime() / 1000 % 60);

    if (m_gameTimer.isActive())
        outputTime = minutes + ":" + seconds;
    else
        outputTime = "15:00";
    return outputTime;
}


void GameController::turnUp()
{
    if(!m_gameTimer.isActive())
        m_gameTimer.start();
    ++m_turns;

    emit nextTurn();
}

void GameController::reset()
{
    m_turns = 0;
    m_gameTimer.stop();
    emit nextTurn();
}

void GameController::saveBestScore()
{
    if ((m_turns < m_bestScore) || (m_bestScore == 0))
    {
        m_bestScore = m_turns;
        QFile file("bestScore.txt");

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
            return;

            QString line;
            QTextStream out(&file);
            line = QString::number(m_bestScore);
            out << m_bestScore;
            file.close();

    }
    emit refreshBestScore();
}
