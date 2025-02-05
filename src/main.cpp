#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qjsvalue.h>

#include "api/geminiapi.h"
#include "api/message.h"
#include "api/messagemodel.h"
#include "utils/Logger.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<GeminiAPI>("GeminiAPI", 1, 0, "GeminiAPI");
    qmlRegisterType<Message>("GeminiAPI", 1, 0, "Message");
    qmlRegisterType<MessageModel>("GeminiAPI", 1, 0, "MessageModel");
    qmlRegisterSingletonType<Logger>("Logger", 1, 0, "Logger", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        QQmlEngine::setObjectOwnership(&Logger::getInstance(), QQmlEngine::CppOwnership);
        return &Logger::getInstance();
    });

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/APITest/resources/qml/Main.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
