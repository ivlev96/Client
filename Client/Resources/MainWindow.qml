import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ApplicationWindow 
{
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("SunChat")

	StackLayout 
	{
		id: mainWindowLayout

		anchors.fill: parent ? parent : undefined
		currentIndex: 0
    
		Authorization{}
	
		Registration{}

		LastMessagesListView{}

		Messages{}

	}
}