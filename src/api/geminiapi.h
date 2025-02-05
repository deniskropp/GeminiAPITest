#ifndef GEMINIAPI_H
#define GEMINIAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>
#include <QJsonArray>

class GeminiAPI : public QObject
{
    Q_OBJECT
public:
    explicit GeminiAPI(QObject *parent = nullptr) : QObject(parent){
        networkManager = new QNetworkAccessManager(this);
    }

    Q_INVOKABLE void generateContent(const QString &apiKey, const QString &promptText);

signals:
    void contentChunkGenerated(const QString &result);
    void errorOccured(const QString &errorMsg);
    void streamFinished();

private:
    QNetworkAccessManager *networkManager;

    QByteArray buffer;
};

#endif // GEMINIAPI_H
