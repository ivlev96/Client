import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item
{
    id: root

    enum ContentWidgets
    {
        LastMessages = 0,
        Messages
    }

    function switchToMessages()
    {
        contentLayout.currentIndex = 1
    }

    StackLayout
    {
        id: contentLayout
        anchors.fill: root

        LastMessagesListView
        {
            id: lastMessagesListView
            objectName: "lastMessagesListView"
        }

        Item
        {
            id: messagesItem

            ToolButton
            {
                id: buttonBack
                text: "\u25C0"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked:
                {
                    contentLayout.currentIndex = 0
                }
            }
            Messages
            {
                id: messages
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: buttonBack.bottom
                anchors.topMargin: 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                objectName: "messages"
            }
        }
    }
}
