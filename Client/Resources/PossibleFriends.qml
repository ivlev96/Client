import QtQuick 2.0
import QtQuick.Controls 2.5

Item
{
    id: root
    signal findFriends(string name, bool withMessages, bool withoutMessages);

    Rectangle
    {
        id: friendNameRect

        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: buttonFind.left
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 0

        height: 24
        radius: 10
        border.width: 1
        border.color: "lightgreen"

        TextInput
        {
            id: filterFriends

            anchors.margins: 5
            anchors.fill: parent

            font.pixelSize: 14

            clip: true
            selectByMouse: true

            Keys.onReturnPressed:
            {
                root.findFriends(filterFriends.text, withMessages.checked || both.checked, withoutMessages.checked || both.checked)
            }

            Keys.onEnterPressed:
            {
                root.findFriends(filterFriends.text, withMessages.checked || both.checked, withoutMessages.checked || both.checked)
            }

            MouseArea
            {
                anchors.margins: 0
                anchors.fill: parent
                cursorShape: Qt.IBeamCursor
                acceptedButtons: Qt.NoButton
            }
        }
    }

    RoundButton
    {
        id: buttonFind

        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: friendNameRect.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        radius: 10

        text: "Find"
        font.pointSize: 10

        onClicked:
        {
            root.findFriends(filterFriends.text, withMessages.checked || both.checked, withoutMessages.checked || both.checked)
        }
    }

    Item
    {
        id: findProperties
        height: 3*withMessages.height + 4*withMessages.anchors.topMargin

        anchors.top: friendNameRect.bottom
        anchors.topMargin: 5


        RadioButton
        {
            id: withMessages

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 10
            checked: false

            height: withMessages.font.pixelSize

            indicator.height: withMessages.font.pixelSize
            indicator.width: indicator.height

            text: "With Messages"
            anchors.topMargin: 5
            font.pixelSize: 14
        }

        RadioButton
        {
            id: withoutMessages

            anchors.top: withMessages.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10

            height: withoutMessages.font.pixelSize

            indicator.height: withoutMessages.font.pixelSize
            indicator.width: indicator.height

            text: "Without Messages"
            checked: false
            anchors.topMargin: 5
            font.pixelSize: 14
        }

        RadioButton
        {
            id: both

            anchors.top: withoutMessages.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            height: both.font.pixelSize

            indicator.height: both.font.pixelSize
            indicator.width: indicator.height

            text: "Both"
            checked: true
            anchors.topMargin: 5
            font.pixelSize: 14
        }
    }

    PossibleFriendsListView
    {
        id: possibleFriendsListView
        objectName: "possibleFriendsListView"

        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: findProperties.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
    }
}
