import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item
{
    id: root

    signal sendMessage(string text)

    MessagesListView
    {
        id: messagesListView
        height: parent.height*0.8
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
    }

    Rectangle
    {
        id: newMessageRect
        width: parent.width*0.8
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: messagesListView.bottom
        anchors.topMargin: 5

        border.color: "lightgreen"
        border.width: 1
        radius: 10

        TextEdit
        {
            id: newMessage
            anchors.margins: 5
            anchors.fill: parent
            font.pixelSize: 14
        }
    }

    RoundButton
    {
        id: buttonSend
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: newMessageRect.right
        anchors.leftMargin: 5
        anchors.top: messagesListView.bottom
        anchors.topMargin: 5

        radius: 10

        text: "Send"
        font.pointSize: 10

        onClicked:
        {
            root.sendMessage(newMessage.text)
            newMessage.clear()
        }
    }
}
