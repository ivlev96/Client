import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Rectangle
{
    id: root
    radius: 10
    border.color: "lightgreen"
    border.width: 1

    ListView
    {
        id: messagesListView
        objectName: "messagesListView"
        anchors.topMargin: 3
        anchors.bottomMargin: 3
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.fill: parent
        spacing: 10
        model: messagesModel

        boundsBehavior: Flickable.StopAtBounds
        clip: true

        ScrollBar.vertical: ScrollBar
        {
            policy: ScrollBar.AsNeeded
        }

        delegate: MessagesDelegate{}

        Connections
        {
            target: messagesModel
            onScrollTo:
            {
                messagesListView.currentIndex = row
            }
        }
    }
}
