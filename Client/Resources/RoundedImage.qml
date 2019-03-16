import QtQuick 2.12
import QtGraphicalEffects 1.12

Image
{
    id: root
    anchors.fill: parent

    layer.enabled: true
    layer.effect: OpacityMask
    {
        maskSource: Item
        {
            width: root.width
            height: root.height
            Rectangle
            {
                anchors.centerIn: parent
                width: root.width
                height: root.height
                radius: Math.min(width, height)
            }
        }
    }
}
