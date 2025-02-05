pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Window
import QtQuick.Controls
import GeminiAPI 1.0

ApplicationWindow {
    id: app
    width: 640
    height: 480
    visible: true
    title: qsTr("Gemini API")

    property bool generating: false;

    GeminiAPI {
        id: geminiAPI
        onContentChunkGenerated: (result) => {
            resultText.text += result
        }
        onErrorOccured: (errorMsg) => {
            resultText.text = errorMsg
            app.generating = false
        }
        onStreamFinished: {
            app.generating = false
        }
    }

    Rectangle {
        id: container
        anchors.fill: parent
        color: "lightgray"

        Column {
            id: c1
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 10
            anchors.margins: 10

            ScrollView{
                id: promptTextScroll
                width: parent.width
                height: app.height * .3
                clip: true

                TextArea{
                    id: promptTA
                    width: parent.width
                    placeholderText: "Enter prompt..."
                }
            }

            Button{
                id: generateContentBtn
                text: "Generate content"
                enabled: !app.generating

                onClicked: {
                    resultText.text = ""
                    app.generating = true
                    geminiAPI.generateContent("", promptTA.text)
                }
            }

            ScrollView{
                id: resultTextScroll
                width: parent.width
                height: parent.height * .3
                clip: true
                visible: false

                TextArea{
                    id: resultText
                    width: parent.width
                    wrapMode: Text.WordWrap
                    text: "Text will appear here"
                    readOnly: true
                }
            }
        }

        Column {
            id: c2
            anchors.top: c1.bottom
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10
            ListView {
                id: messagesView
                width: parent.width
                height: parent.height// * .3
                clip: true
                model: geminiAPI.getMessageModel()
                spacing: 1
                delegate: Rectangle {
                    id: messageDelegate

                    required property bool isUser
                    required property string text

                    width: messagesView.width
                    radius: 2
                    border.width: 1
                    border.color: "red"
                    height: childrenRect.height + 10
                    color: isUser ? "lightblue" : "lightgreen"

                    Column {
                        spacing: 10

                        Text {
                            text: messageDelegate.isUser ? "User" : "Model"
                            font.bold: true
                            topPadding: 5
                            leftPadding: 10
                        }

                        Text {
                            text: messageDelegate.text
                            wrapMode: Text.WordWrap
                            leftPadding: 10
                        }
                    }
                }
            }
        }
    }
}
