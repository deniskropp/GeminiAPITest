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

#include "messagemodel.h"

class GeminiAPI : public QObject
{
    Q_OBJECT
public:
    explicit GeminiAPI(QObject *parent = nullptr);

    Q_INVOKABLE void generateContent(const QString &apiKey, const QString &promptText);
    Q_INVOKABLE MessageModel* getMessageModel();

signals:
    void contentChunkGenerated(const QString &result);
    void errorOccured(const QString &errorMsg);
    void streamFinished();

private:
    QNetworkAccessManager *networkManager;
    MessageModel *messageModel;
};

#endif // GEMINIAPI_H
