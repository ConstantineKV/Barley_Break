#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <gameboard.h>
#include <gamecontroller.h>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    GameController* gameController = new GameController();
    qmlRegisterType<GameBoard>("Game", 1, 0, "GameBoardModel");
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    //QQuickWidget *myObject = static_cast<QQuickWidget*>(engine.rootObjects().first());
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("gameController", gameController);
    engine.load(url);

    return app.exec();
}
