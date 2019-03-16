import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Rectangle
{
    id: root
    radius: 10
    anchors.margins: 10
    border.color: "lightgreen"
    border.width: 1

    signal itemClicked(int index)

    ListView
    {
        anchors.topMargin: root.radius
        anchors.bottomMargin: root.radius
        anchors.leftMargin: root.border.width
        anchors.rightMargin: root.border.width
        anchors.fill: parent
        model: lastMessagesModel

        boundsBehavior: Flickable.StopAtBounds
        clip: true

        ScrollBar.vertical: ScrollBar
        {
            policy: ScrollBar.AsNeeded
        }
        delegate: LastMessagesDelegate{}

        highlightFollowsCurrentItem: false
    }
}
