import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item
{
    id: element
    MessagesListView
    {
        id: messagesListView
        height: parent.height*0.8
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        transformOrigin: Item.Center
    }

    TextEdit
    {
        id: newMessage
        width: parent.width*0.8
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: messagesListView.bottom
        anchors.topMargin: 0
        font.pixelSize: 12
    }

    Button
    {
        id: buttonSend
        text: "Button"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: newMessage.right
        anchors.leftMargin: 0
        anchors.top: messagesListView.bottom
        anchors.topMargin: 0
    }
}
