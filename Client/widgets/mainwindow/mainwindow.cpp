#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorization/authorizationinfo.h"
#include "widgets/registration/registration.h"
#include "widgets/authorization/authorization.h"
#include "widgets/lastmessages/lastmessages.h"
#include "widgets/messages/messages.h"
#include "models/messagesmodel.h"
#include "models/lastmessagesmodel.h"

using namespace Widgets;

MainWindow::MainWindow(Models::LastMessagesModel* lastMessagesModel,
	Models::MessagesModel* messagesModel,
	QWidget *parent)
	: QMainWindow(parent)
{
	m_ui = std::make_unique<Ui::MainWindow>();
	m_ui->setupUi(this);

	m_authorization = std::make_unique<Authorization>();
	m_registration = std::make_unique<Registration>();
	m_lastMessages = std::make_unique<LastMessages>(lastMessagesModel);
	m_messages = std::make_unique<Messages>(messagesModel);

	m_layout = std::make_unique<QStackedLayout>();
	m_ui->centralWidget->setLayout(m_layout.get());

	m_layout->addWidget(m_authorization.get());
	m_layout->addWidget(m_registration.get());
	m_layout->addWidget(m_lastMessages.get());
	m_layout->addWidget(m_messages.get());

	switchToAuthorization();

	VERIFY(connect(m_authorization.get(), &Authorization::error, this, &MainWindow::error));
	VERIFY(connect(m_authorization.get(), &Authorization::signUpClicked, this, &MainWindow::switchToRegistration));	
	VERIFY(connect(m_authorization.get(), &Authorization::logIn, this, &MainWindow::logIn));

	VERIFY(connect(m_registration.get(), &Registration::logInClicked, this, &MainWindow::switchToAuthorization));	
	VERIFY(connect(m_registration.get(), &Registration::signUp, this, &MainWindow::signUp));
	
	VERIFY(connect(m_lastMessages.get(), &LastMessages::personSelected, this, &MainWindow::onPersonSelected));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showError(const QString& error) const
{
	m_ui->statusBar->showMessage(error, 2000);
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
	m_messages->setPerson(person);
	switchToMessages();
}

void MainWindow::switchToRegistration()
{
	m_layout->setCurrentWidget(m_registration.get());
}

void MainWindow::switchToAuthorization()
{
	m_layout->setCurrentWidget(m_authorization.get());
}

void MainWindow::switchToLastMessages()
{
	m_layout->setCurrentWidget(m_lastMessages.get());
}

void MainWindow::switchToMessages()
{
	m_layout->setCurrentWidget(m_messages.get());
}
