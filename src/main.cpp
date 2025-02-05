#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "api/geminiapi.h"
#include "api/message.h"
#include "api/messagemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    GeminiAPI geminiAPI;
//    QString apiKey = "AIzaSyCQ2P-Imyhc7dGiq2VxmqpIncAMP8BUy6U";
//    QString promptText = "Explain how AI works";

//    geminiAPI.generateContent(apiKey, promptText);

    qmlRegisterType<GeminiAPI>("GeminiAPI", 1,0, "GeminiAPI");
    qmlRegisterType<Message>("GeminiAPI", 1, 0, "Message");
    qmlRegisterType<MessageModel>("GeminiAPI", 1, 0, "MessageModel");

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/APITest/resources/qml/Main.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
