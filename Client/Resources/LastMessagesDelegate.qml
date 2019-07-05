import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Rectangle
{
    id: root
    height: 60
    width: lastMessagesListView.width
    color: mouseArea.containsMouse ? "lightgreen" : "white"

    Rectangle
    {
        id: avatar
        width: height
        radius: width/2
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5

        RoundedImage
        {
            source: messageAvatar
        }
    }

    Text
    {
        id: author
        font.pointSize: 9
        textFormat: Text.RichText
        text: "<b>" + messageAuthor + "</b>"
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: avatar.right
        anchors.leftMargin: 10
        //selectByMouse: true
    }

    Text
    {
        id: time
        font.pointSize: 9
        textFormat: Text.RichText
        text: "<font color=\"grey\">" + messageTime + "</font>"
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        //selectByMouse: true
    }

    Text
    {
        id: shortAuthor
        font.pointSize: 9
        textFormat: Text.RichText
        text: "<font color=\"grey\">" + messageShortAuthor + ":</font>"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: avatar.right
        anchors.leftMargin: 10
        //selectByMouse: true
    }

    Text
    {
        id: message
        text: messageText
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: shortAuthor.bottom
        anchors.bottomMargin: 0
        anchors.left: shortAuthor.right
        anchors.leftMargin: 5

        font.pointSize: 9
        textFormat: Text.PlainText

        elide: Qt.ElideRight
    }

    Rectangle //separator
    {
        anchors.bottom: root.bottom
        id: lowerBorder
        width: root.width
        height: 1

        gradient: Gradient
        {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "grey" }
            GradientStop { position: 1.0; color: "white" }
            orientation: Qt.Horizontal
        }

        visible: index + 1 < lastMessagesListView.count
    }

    MouseArea
    {
        hoverEnabled: true
        id: mouseArea
        anchors.fill: root
        onClicked:
        {
            if (Qt.platform.os === "android")
            {
                content.switchToMessages()
            }
            lastMessagesListView.itemClicked(index)
        }
    }
}
