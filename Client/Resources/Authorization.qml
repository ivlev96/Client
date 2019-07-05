import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import cppnamespace 1.0

Item
{
    id: root

    signal logIn(string login, string password)

    ColumnLayout 
	{
        anchors.centerIn: parent

        Label 
		{
            id: label
            text: "Authorization"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 10
            textFormat: Text.PlainText
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
        }

        TextField 
		{
            id: login
            horizontalAlignment: Text.AlignLeft
            placeholderText: "Login"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredWidth: 120
            selectByMouse: true
        }

        TextField 
		{
            id: password
            placeholderText: "Password"
            placeholderTextColor: "lightgrey"
            font.pointSize: 10
            Layout.fillWidth: true
            Layout.preferredWidth: 120
			echoMode: TextInput.Password
            selectByMouse: true
        }

        Button 
		{
            id: logInButton
            text: "Log In"
            font.pointSize: 10
            Layout.fillWidth: true

            onClicked:
            {
                root.logIn(login.text, password.text)
            }
        }
    }

    Button 
	{
        id: switchToSignUpButton
        width: 120
        text: "Sign Up"
        font.pointSize: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8

        onClicked: mainWindowLayout.currentIndex = Widgets.Registration
    }

}
