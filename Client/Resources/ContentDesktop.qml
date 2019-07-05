import QtQuick 2.12
import QtQuick.Controls 2.5

Item
{
    id: root

    LastMessagesListView
    {
        id: lastMessagesListView

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: friendNameRect.bottom
        anchors.topMargin: 5
        anchors.bottom: buttonOpenFindWidget.top
        anchors.bottomMargin: 5

        width: 220

        objectName: "lastMessagesListView"
    }

    Rectangle
    {
        id: friendNameRect
        height: 24

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: lastMessagesListView.right
        anchors.rightMargin: 0


        border.color: "lightgreen"
        border.width: 1
        radius: 10
        anchors.top: parent.top
        anchors.topMargin: 5


        TextInput
        {
            id: friendSearchText
            objectName: "friendSearchText"

            signal friendSearchTextChanged(string text)
            anchors.bottomMargin: 5

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

            onTextChanged: friendSearchTextChanged(text)
        }
    }

    RoundButton
    {
        id: buttonOpenFindWidget

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        radius: 10

        text: "Find Friends!"
        anchors.right: lastMessagesListView.right
        anchors.rightMargin: 0
        font.pointSize: 10

        onClicked:
        {
            //root.findFriend(friendSearchText.text)
        }
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
