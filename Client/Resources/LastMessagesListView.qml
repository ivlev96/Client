import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ListView
{
    id: lastMessagesListView
    anchors.margins: 10
    width: parent ? parent.width : undefined
    height: parent ? parent.height : undefined
    //model: listModel

    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar
    {
        policy: ScrollBar.AsNeeded
    }
    delegate: LastMessagesDelegate
    {
        width: lastMessagesListView.width
    }
    highlightFollowsCurrentItem: false

    signal itemClicked(int index)
}
