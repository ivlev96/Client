import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Rectangle
{
	id: delegateRect
	height: 80

	GridLayout
    {
        id: globalLayout
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent

		columns: 2
		rows: 2
        columnSpacing: 10
        rowSpacing: 10

        Rectangle
		{
			Layout.row: 0
			Layout.column: 0
			Layout.rowSpan: 2
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

            height: delegateRect.height - globalLayout.anchors.topMargin - globalLayout.anchors.bottomMargin
			width: height
			radius: width/2

            RoundedImage
            {
				source: messageAvatar
			}
		}

		RowLayout
        {
            id: headerLayout

            Layout.row: 0
            Layout.column: 1

			TextEdit
			{
				Layout.column: 0

				font.pointSize: 8
				textFormat: TextEdit.RichText
				text: "<b>" + messageAuthor + "</b>"
				selectByMouse: true
			}
				
			TextEdit
			{
				Layout.column: 1

				font.pointSize: 8
				textFormat: TextEdit.RichText
				text: "<font color=\"grey\">" + messageTime + "</font>"
				selectByMouse: true
			}
		}

			
		RowLayout
		{
			id: messageTextLayout

			Layout.row: 1
			Layout.column: 1

			TextEdit
			{
				Layout.column: 0

				font.pointSize: 8
				textFormat: TextEdit.RichText
				text: "<font color=\"grey\">" + messageShortAuthor + ":</font>"
				selectByMouse: true
			}
				
			TextEdit
			{
				Layout.column: 1

				font.pointSize: 8
				textFormat: TextEdit.RichText
				text: messageText
				selectByMouse: true
			}
        }

        Item
        {
            Layout.row: 0
            Layout.column: 2
            Layout.rowSpan: 2

            // spacer item
            Layout.fillWidth: true
            Layout.fillHeight: true // to visualize the spacer
        }
	}
}
