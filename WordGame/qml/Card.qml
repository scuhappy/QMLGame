import QtQuick 2.0

Item {
    property alias wordContent: wordText.text
    Rectangle{
        color: "white"
        anchors.fill: parent
        radius: 20
        Text{
            id : wordText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: ""
            font.pixelSize: 32
        }
    }
}
