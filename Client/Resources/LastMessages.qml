import QtQuick 2.0

Item
{
    id: root

    Rectangle
    {
        id: friendNameRect

        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        height: 24
        radius: 10
        border.width: 1
        border.color: "lightgreen"

        TextInput
        {
            id: filterFriends
            objectName: "filterFriends"

            signal filterFriendsTextChanged(string text)

            anchors.margins: 5
            anchors.fill: parent

            font.pixelSize: 14

            clip: true
            selectByMouse: true

            MouseArea
            {
                anchors.margins: 0
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }

            onTextChanged: filterFriendsTextChanged(text)
        }
    }

    LastMessagesListView
    {
        id: lastMessagesListView
        objectName: "lastMessagesListView"

        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: friendNameRect.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
    }
}
