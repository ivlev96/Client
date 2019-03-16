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

    enum WidgetNum {
        Authorization = 1,
        Registration,
        LastMessagesListView,
        Messages
    }

    StackLayout
    {
        id: mainWindowLayout

        anchors.fill: parent
        currentIndex: 0

        Authorization
        {
            id: authorization
        }

        Registration
        {
            id: registration
        }

        ContentMobile
        {
            id: content
        }
    }
}
