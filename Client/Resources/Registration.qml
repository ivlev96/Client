import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import cppnamespace 1.0

Item
{
    id: root

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            id: label
            text: "Registration"
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
            Layout.preferredWidth: 120
        }

        TextField {
            id: lastName
            placeholderText: "Last name"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredWidth: 120
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
            Layout.preferredWidth: 120
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
            Layout.preferredWidth: 120
			echoMode: TextInput.Password
        }

        TextField {
            id: repeatPassword
            placeholderText: "Repeat password"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredWidth: 120
			echoMode: TextInput.Password
        }

        Button {
            id: registerButton
            text: "Register"
            font.pointSize: 10
            Layout.fillWidth: true
        }
    }

    Button {
        id: switchToLogInButton
        width: 120
        text: "Log In"
        font.pointSize: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
		
        onClicked: mainWindowLayout.currentIndex = Widgets.Authorization
    }

}
