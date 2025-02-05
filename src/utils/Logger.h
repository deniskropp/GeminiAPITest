#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

class Logger : public QObject
{
    Q_OBJECT

public:
    enum LogLevel {
        INFO,
        DEBUG,
        ERROR
    };

    static void log(LogLevel level, const QString &message);

private:
    static QString logLevelToString(LogLevel level);
    static QString currentDateTime();
};

#endif // LOGGER_H
