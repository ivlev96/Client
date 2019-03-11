import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item
{
    id: authorization

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
            id: login
            horizontalAlignment: Text.AlignLeft
            placeholderText: "Login"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            font.weight: Font.Thin
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.preferredWidth: 80
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

        Button {
            id: logInButton
            text: "Log In"
            font.pointSize: 10
            Layout.fillWidth: true
        }
    }

    Button {
        id: signUpButton
        x: 270
        y: 432
        text: "Sign Up"
        font.pointSize: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
    }

}
