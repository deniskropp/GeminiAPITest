#include "geminiapi.h"

void GeminiAPI::generateContent(const QString &apiKey, const QString &promptText) {
    // Correct URL for the API endpoint
    QUrl url("https://generativelanguage.googleapis.com/v1beta2/models/gemini-1.5-flash:generateText");

    // Create the network request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Set Authorization with Bearer token
    request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());

    // Create JSON body
    QJsonObject requestBody;
    QJsonObject prompt;
    prompt["text"] = promptText;  // Add the prompt text
    requestBody["prompt"] = prompt;

    // Convert JSON to QByteArray
    QJsonDocument jsonDoc(requestBody);
    QByteArray jsonData = jsonDoc.toJson();

    // Send POST request
    QNetworkReply *reply = networkManager->post(request, jsonData);

    // Handle response when finished
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            emit contentGenerated(QString(responseData));
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
