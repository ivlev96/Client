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

        Flickable
        {
            id: newMessageFlickable

            anchors.margins: 5
            anchors.fill: parent

            contentWidth: newMessage.paintedWidth
            contentHeight: newMessage.paintedHeight
            clip: true

            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar
            {
                policy: ScrollBar.AsNeeded
            }

            function ensureVisible(r)
            {
                if (contentX >= r.x)
                  contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                  contentX = r.x+r.width-width;
                if (contentY >= r.y)
                  contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                  contentY = r.y+r.height-height;
            }


            TextEdit
            {
                id: newMessage

                width: newMessageFlickable.width
                Layout.minimumHeight: newMessageFlickable.height

                font.pixelSize: 14
                selectByMouse: true

                wrapMode: TextEdit.Wrap
                clip: true

                onCursorRectangleChanged: newMessageFlickable.ensureVisible(cursorRectangle)

                MouseArea //TODO: fill whole flickable and catch mouse click to activate newMessage
                {
                    anchors.fill: parent
                    cursorShape: Qt.IBeamCursor
                    acceptedButtons: Qt.NoButton
                }
            }
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
