#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlEngine>
#include <qtmetamacros.h>

class Logger : public QObject
{
    Q_OBJECT

public:
    enum LogLevel {
        INFO,
        DEBUG,
        ERROR
    };
    Q_ENUM(LogLevel)

    static Logger& getInstance() {
        static Logger instance;
        QQmlEngine::setObjectOwnership(&instance, QQmlEngine::CppOwnership);
        return instance;
    }

    Q_INVOKABLE void log(LogLevel level, const QString &message);

    Q_INVOKABLE void info(const QString &message) { log(INFO, message); }
    Q_INVOKABLE void debug(const QString &message) { log(DEBUG, message); }
    Q_INVOKABLE void error(const QString &message) { log(ERROR, message); }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() = default;
    ~Logger() = default;

    QString logLevelToString(LogLevel level);
    QString currentDateTime();
};

#endif // LOGGER_H