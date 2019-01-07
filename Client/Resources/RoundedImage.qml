import QtQuick 2.12
import QtGraphicalEffects 1.12

Image
{
    id: img
    anchors.fill: parent

    layer.enabled: true
    layer.effect: OpacityMask
    {
        maskSource: Item
        {
            width: img.width
            height: img.height
            Rectangle
            {
                anchors.centerIn: parent
                width: img.width
                height: img.height
                radius: Math.min(width, height)
            }
        }
    }
}
