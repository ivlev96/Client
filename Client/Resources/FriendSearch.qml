import QtQuick 2.12
import QtQuick.Controls 2.5

Item
{
    id: root
    height: friendName.font.pixelSize + 20

    RoundButton
    {
        id: buttonSearch
        width: text.length * font.pixelSize
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5

        radius: 10

        text: "Search"
        font.pointSize: 10

        onClicked:
        {
            root.findFriend(friendName.text)
        }
    }

    Rectangle
    {
        id: friendNameRect

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: buttonSearch.left
        anchors.rightMargin: 5

        border.color: "lightgreen"
        border.width: 1
        radius: 10

        TextInput
        {
            id: friendName
            anchors.margins: 5
            anchors.fill: parent
            font.pixelSize: 14
            clip: true
            selectByMouse: true
            MouseArea
            {
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }
    }
}
