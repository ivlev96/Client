import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ListView
{
    id: messagesListView
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
	
    delegate: MessagesDelegate{}

	Connections 
	{
		target: listModel 
		onScrollTo: 
		{
			messagesListView.currentIndex = row
		}
	}
}
