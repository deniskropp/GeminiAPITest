import QtQuick
import QtQuick.Window
import QtQuick.Controls
import GeminiAPI 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Gemini API")

    GeminiAPI{
        id: geminiAPI
        onContentGenerated:{
            resultText.text = result
        }
        onErrorOccured:{
            resultText.text = errorMsg
        }
    }

    Rectangle{
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
            anchors{
                right: promptTA.right
                top: promptTA.bottom
                topMargin: 10
            }

            onClicked: {
                geminiAPI.generateContent("AIzaSyCQ2P-Imyhc7dGiq2VxmqpIncAMP8BUy6U", promptTA.text)
            }
        }

        Text{
            id: resultText
            anchors{
                left: parent.left
                leftMargin: 10
                top: generateContentBtn.bottom
                topMargin: 10
            }
            wrapMode: Text.WordWrap
            text: "Text will appear here"
        }
    }

//    Connections{
//        target: geminiAPI
//        onContentGenerated:{
//            resultText.text = result
//        }
//        onErrorOccured:{
//            resultText.text = erroMsg
//        }
//    }
}













