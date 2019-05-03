import QtQuick 2.12

Item
{
    id: root

    FriendSearch
    {
        id: friendSearch
        width: parent.width * 0.3

        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    LastMessagesListView
    {
        id: lastMessagesListView
        anchors.right: friendSearch.right
        anchors.rightMargin: 0
        objectName: "lastMessagesListView"
        anchors.top: friendSearch.bottom
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
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
