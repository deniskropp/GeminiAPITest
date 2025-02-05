#include "Logger.h"

void Logger::log(LogLevel level, const QString &message)
{
    QJsonObject logObject;
    logObject["timestamp"] = currentDateTime();
    logObject["level"] = logLevelToString(level);
    logObject["message"] = message;

    QJsonDocument doc(logObject);
    QString logEntry = doc.toJson(QJsonDocument::Compact);

    QFile file("app.log");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logEntry << "\n";
        file.close();
    }
}

QString Logger::logLevelToString(LogLevel level)
{
    switch (level) {
        case INFO:
            return "INFO";
        case DEBUG:
            return "DEBUG";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

QString Logger::currentDateTime()
{
    return QDateTime::currentDateTime().toString(Qt::ISODate);
}
