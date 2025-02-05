#include "geminiapi.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QUrlQuery>
#include <qjsondocument.h>
#include <qstringview.h>
#include <qtenvironmentvariables.h>

GeminiAPI::GeminiAPI(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    messageModel = new MessageModel(this);
}

void GeminiAPI::generateContent(const QString &apiKey, const QString &promptText) {
    QString key = apiKey.isEmpty() ? qEnvironmentVariable("GEMINI_API_KEY") : apiKey;

    messageModel->addMessage(promptText, true);

    // Construct the URL with the API key as a query parameter
    QUrl url("https://generativelanguage.googleapis.com/v1beta/models/"
             "gemini-2.0-flash-exp:streamGenerateContent");
    QUrlQuery query;
    query.addQueryItem("key", key);
    url.setQuery(query);

    // Create the network request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // (Optional but recommended) Set the x-goog-api-key header
    request.setRawHeader("x-goog-api-key", key.toUtf8());

    // Create the correct JSON body for the Gemini API
    QJsonObject requestBody;
    QJsonArray contentsArray;
    QJsonObject contentObject;
    QJsonArray partsArray;
    QJsonObject partObject;

    partObject["text"] = promptText;
    partsArray.append(partObject);
    contentObject["parts"] = partsArray;
    contentsArray.append(contentObject);
    requestBody["contents"] = contentsArray;

    // Convert JSON to QByteArray
    QJsonDocument jsonDoc(requestBody);
    QByteArray jsonData = jsonDoc.toJson();

    // Send POST request
    QNetworkReply *reply = networkManager->post(request, jsonData);

    connect(reply, &QNetworkReply::readyRead, this, [this, reply]() {
        QByteArray all = reply->readAll();

        QList<QByteArray> chunks = all.split('\r');

        for (const auto &chunk : chunks) {
            // Handle each chunk here
            QByteArray data = chunk;

            //qDebug() << "\n\n" << data << "\n\n";

            if (data == "]")
                return;

            if (data.startsWith("[") || data.startsWith(","))
                data = data.mid(1);

            if (data.endsWith("]"))
                data = data.mid(0, data.size() - 1);

            if (data.endsWith(","))
                data = data.mid(0, data.size() - 1);

            if (!data.isEmpty()) {
                QJsonParseError error;
                QJsonDocument doc = QJsonDocument::fromJson(data, &error);

                if (error.error == QJsonParseError::NoError) {
                    if (doc.isObject()) {
                        QJsonObject root = doc.object();
                        if (root.contains("candidates") && root["candidates"].isArray()) {
                            QJsonArray candidates = root["candidates"].toArray();
                            if (!candidates.isEmpty() && candidates[0].isObject()) {
                                QJsonObject candidate = candidates[0].toObject();
                                if (candidate.contains("content") && candidate["content"].isObject()) {
                                    QJsonObject content = candidate["content"].toObject();
                                    if (content.contains("parts") && content["parts"].isArray()) {
                                        QJsonArray parts = content["parts"].toArray();
                                        if (!parts.isEmpty() && parts[0].isObject()) {
                                            QJsonObject part = parts[0].toObject();
                                            if (part.contains("text") && part["text"].isString()) {
                                                //qDebug() << "\n\n::" << part["text"].toString() << "::\n\n";
                                                emit contentChunkGenerated(part["text"].toString());

                                                if (messageModel->rowCount() == 0 || messageModel->data(messageModel->index(messageModel->rowCount() - 1), MessageModel::IsUserRole).toBool())
                                                    messageModel->addMessage(part["text"].toString(), false);
                                                else
                                                    messageModel->appendToLastMessage(part["text"].toString());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    qDebug() << "JSON parsing error:" << error.errorString() << "\n\n" << data << "\n\n";
                    emit errorOccured(error.errorString());
                }
            }
        }
    });

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Optionally signal end of streaming
            emit streamFinished();
        } else {
            // Print error details
            qDebug() << "Error:" << reply->errorString();
            qDebug() << "HTTP status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << "Response headers:" << reply->rawHeaderList();
            qDebug() << "Response body:" << reply->readAll();
            emit errorOccured(reply->errorString());
        }
        reply->deleteLater();
    });
}

MessageModel *GeminiAPI::getMessageModel() {
    return messageModel;
}
