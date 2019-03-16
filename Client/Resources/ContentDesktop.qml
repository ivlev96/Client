import QtQuick 2.12

Item
{
    id: element
    LastMessagesListView
    {
        id: lastMessagesListView
        objectName: "lastMessagesListView"
        width: parent.width * 0.3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
    }

    Messages
    {
        id: messages
        objectName: "messages"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: lastMessagesListView.right
        anchors.leftMargin: 0
    }

}
