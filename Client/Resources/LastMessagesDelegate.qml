import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Rectangle
{
	id: delegateRect
	height: 60
	color: mouseArea.containsMouse ? "lightyellow" : "white"

	MouseArea {
		hoverEnabled: true
		id: mouseArea
		anchors.fill: delegateRect
		onClicked: lastMessagesListView.itemClicked(index)
	}

	GridLayout
    {
        id: globalLayout
        anchors.rightMargin: 15
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent

		columns: 2
		rows: 2
        columnSpacing: 10
        rowSpacing: 10

        Rectangle
		{
			id: avatar
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

				font.pointSize: 9
				textFormat: TextEdit.RichText
				text: "<b>" + messageAuthor + "</b>"
				selectByMouse: true
			}

			Item
			{
				Layout.column: 1
				Layout.fillWidth: true
			}
				
			TextEdit
			{
				Layout.column: 2

				font.pointSize: 9
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
				id: shortAuthor
				Layout.column: 0

				font.pointSize: 9
				textFormat: TextEdit.RichText
				text: "<font color=\"grey\">" + messageShortAuthor + ":</font>"
				selectByMouse: true
			}
				
			Text
			{
				Layout.column: 1

				font.pointSize: 9
				textFormat: Text.PlainText
				text: messageText
				Layout.preferredWidth: delegateRect.width - 
					avatar.width - 
					globalLayout.anchors.leftMargin - 
					globalLayout.anchors.rightMargin - 
					globalLayout.columnSpacing - 
					shortAuthor.width
				elide: Qt.ElideRight
			}
        }
	}

	Rectangle //separator
	{
		anchors.bottom: delegateRect.bottom
		id: lowerBorder
		width: delegateRect.width
		height: 1

		gradient: Gradient
		{
			GradientStop { position: 0.0; color: "white" }
			GradientStop { position: 0.5; color: "grey" }
			GradientStop { position: 1.0; color: "white" }
			orientation: Qt.Horizontal
		}

		visible: index + 1 < lastMessagesListView.count
	}
}
