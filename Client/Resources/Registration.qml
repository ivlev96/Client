import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item
{
    id: element

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            id: label
            text: "Authorization"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 10
            textFormat: Text.PlainText
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
        }

        TextField {
            id: firstName
            horizontalAlignment: Text.AlignLeft
            placeholderText: "First name"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            font.weight: Font.Thin
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 80
        }

        TextField {
            id: lastName
            placeholderText: "Last name"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 80
        }

        Item {
            id: spacer1
            Layout.fillWidth: true
            height: 15
        }

        TextField {
            id: login
            placeholderText: "Login"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 80
        }

        Item {
            id: spacer2
            Layout.fillWidth: true
            height: 15
        }

        TextField {
            id: password
            placeholderText: "Password"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 80
        }

        TextField {
            id: repeatPassword
            placeholderText: "Repeat password"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 80
        }

        Button {
            id: button
            text: "Register"
            font.pointSize: 10
            Layout.fillWidth: true
        }
    }

    Button {
        id: button1
        x: 270
        y: 432
        text: "Log In"
        display: AbstractButton.TextOnly
        font.pointSize: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
    }

}
