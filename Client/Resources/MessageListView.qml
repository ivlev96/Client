import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ListView
{
    id: customView
    anchors.margins: 10
    width: parent ? parent.width : undefined
    height: parent ? parent.height : undefined
    spacing: 10
    model: listModel

    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar
    {
        policy: ScrollBar.AsNeeded
    }

    delegate: Rectangle
    {
        width: messageLayout.width + 10
        height: messageLayout.height + 10

        radius: 10

        color: "lightgreen"
        anchors.right: messageIsFromMe ? parent.right : undefined
        anchors.left: messageIsFromMe ? undefined : parent.left

        GridLayout
        {
            id: messageLayout
            columns: 2
            rows: 2
            columnSpacing: 10
            anchors.centerIn: parent

            Rectangle
            {
                Layout.row: 0
                Layout.column: 0
                Layout.rowSpan: 2
                Layout.alignment: Qt.AlignTop

                width: 50
                height: width
                radius: width/2

                RoundedImage
                {
                    source: messageAvatar
                }
            }


            TextEdit
            {
                Layout.row: 0
                Layout.column: 1

                font.pointSize: 8
                textFormat: TextEdit.RichText
                text: "<b>" + messageAuthor + "</b> " + "<font color=\"grey\">" + messageTime + "</font>"
                selectByMouse: true
            }

            TextEdit
            {
                Layout.row: 1
                Layout.column: 1

                font.pointSize: 10
                text: messageText
                selectByMouse: true
            }
        }
    }
}
