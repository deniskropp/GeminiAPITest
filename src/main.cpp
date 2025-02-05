#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "api/geminiapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    GeminiAPI geminiAPI;
//    QString apiKey = "AIzaSyCQ2P-Imyhc7dGiq2VxmqpIncAMP8BUy6U";
//    QString promptText = "Explain how AI works";

//    geminiAPI.generateContent(apiKey, promptText);

    qmlRegisterType<GeminiAPI>("GeminiAPI", 1,0, "GeminiAPI");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/APITest/resources/qml/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
