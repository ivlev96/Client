#include "mainwindow.h"
#include "authorization/authorizationinfo.h"
#include "models/messagesmodel.h"
#include "models/lastmessagesmodel.h"

using namespace Widgets;

MainWindow::MainWindow(Models::LastMessagesModel* lastMessagesModel,
	Models::MessagesModel* messagesModel)
	: m_engine()
{
	Q_UNUSED(lastMessagesModel);
	Q_UNUSED(messagesModel);
	m_engine.load(QUrl("qrc:/MainWindow.qml"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showError(const QString& error)
{
	Q_UNUSED(error);
}

void MainWindow::onConnected()
{

}

void MainWindow::onLogInResponse(bool ok, const std::optional<Common::Person>& person)
{
	if (ok)
	{
		::Authorization::AuthorizationInfo::instance().reset(*person);
		switchToLastMessages();
	}
	else
	{
		emit error("Wrong login or password");
	}
}

void MainWindow::onSignUpResponse(bool ok, const std::optional<Common::Person>& person)
{
	if (ok)
	{
		::Authorization::AuthorizationInfo::instance().reset(*person);
		switchToLastMessages();
	}
	else
	{
		emit error("Login is already in use");
	}
}

void MainWindow::onPersonSelected(const Common::Person& person)
{
	Q_UNUSED(person);
	//m_messages->setPerson(person);
	switchToMessages();
}

void MainWindow::switchToRegistration()
{

}

void MainWindow::switchToAuthorization()
{

}

void MainWindow::switchToLastMessages()
{

}

void MainWindow::switchToMessages()
{

}
