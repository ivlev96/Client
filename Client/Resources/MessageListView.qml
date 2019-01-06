import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ListView
{
    id: customView
    anchors.margins: 10
    width: parent.width
    height: parent.height
    spacing: 10
    model: listModel

    delegate: Rectangle
    {
        width: messageLayout.width
        height: messageLayout.height
        color: "lightgreen"
        anchors.right: messageIsFromMe ? parent.right : null
        anchors.left: messageIsFromMe ? null : parent.left

        ColumnLayout
        {
            id: messageLayout
            spacing: 10

            Text
            {
                text: "<b>" + messageName + "</b> " + "<font color=\"grey\">" + messageTime + "</font>"
                //selectByMouse: true
            }

            Text
            {
                //anchors.centerIn: parent
                text: messageText
                //selectByMouse: true
            }
        }
    }
}
