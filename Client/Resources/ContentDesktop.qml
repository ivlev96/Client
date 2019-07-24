import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item
{
    id: root

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
        anchors.left: leftStackView.right
        anchors.leftMargin: 5
    }

    StackLayout
    {
        id: leftStackView
        width: 220
        currentIndex: 0

        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: buttonSwitch.top
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5

        LastMessages
        {
            id: lastMessages
            anchors.fill: parent
        }

        PossibleFriends
        {
            id: possibleFriends
            objectName: "possibleFriends"
            anchors.fill: parent
        }
    }

    RoundButton
    {
        id: buttonSwitch

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        radius: 10

        text: leftStackView.currentIndex == 0 ? "Find Friends!" : "Return to Last Messages"
        anchors.right: leftStackView.right
        anchors.rightMargin: 0
        font.pointSize: 10

        onClicked:
        {
            leftStackView.currentIndex = 1 - leftStackView.currentIndex;
        }
    }
}
