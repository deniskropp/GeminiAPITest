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

        TextArea{
            id: promptTA
            width: parent.width* .95
            height: parent.height* .5
            placeholderText: "Enter prompt..."
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button{
            id: generateContentBtn
            text: "Generate content"
            enabled: !generating

            anchors{
                right: promptTA.right
                top: promptTA.bottom
                topMargin: 10
            }

            onClicked: {
                resultText.text = ""
                app.generating = true
                geminiAPI.generateContent("", promptTA.text)
            }
        }

        ScrollView{
            id: resultTextScroll
            anchors{
                left: parent.left
                leftMargin: 10
                top: generateContentBtn.bottom
                topMargin: 10
                right: parent.right
                rightMargin: 10
                bottom: parent.bottom
                bottomMargin: 10
            }
            clip: true

            TextArea{
                id: resultText
                width: parent.width
                wrapMode: Text.WordWrap
                text: "Text will appear here"
                readOnly: true
            }
        }
    }
}
