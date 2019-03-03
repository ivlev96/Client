#include "globalcontroller.h"
#include "common/common.h"

using namespace Controllers;
using namespace Widgets;
using namespace Models;
using namespace Network;

GlobalController::GlobalController()
	: m_messagesModel(new MessagesModel(this))
	, m_lastMessagesModel(new LastMessagesModel(this))
	, m_requester(new Requester(Common::serverUrl))
	, m_requesterThread(new QThread(this))
{
	qRegisterMetaType<Common::Person>("Person");
	qRegisterMetaType<Common::PersonIdType>("Common::PersonIdType");

	qRegisterMetaType<Common::Message>("Message");
	qRegisterMetaType<Common::MessageIdType>("Common::MessageIdType");
	qRegisterMetaType<std::vector<Common::Message>>("vector<Message>");
	qRegisterMetaType<Common::Message::State>("State");
	qRegisterMetaType<std::optional<Common::Person>>("std::optional<Common::Person>");
	qRegisterMetaType<std::optional<Common::MessageIdType>>("std::optional<Common::MessageIdType>");
	qRegisterMetaType<std::vector<std::pair<Common::Person, Common::Message>>>("std::vector<std::pair<Common::Person,Common::Message>>");

	m_mainWindow = std::make_unique<MainWindow>(m_lastMessagesModel, m_messagesModel);

	m_requester->moveToThread(m_requesterThread);
	VERIFY(connect(m_requesterThread, &QThread::finished, m_requester, &QObject::deleteLater));
	VERIFY(connect(m_requesterThread, &QThread::started, m_requester, &Requester::onThreadStarted));

	//errors
	VERIFY(connect(m_requester, &Requester::error, this, &GlobalController::onError));
	VERIFY(connect(m_messagesModel, &MessagesModel::error, this, &GlobalController::onError));
	VERIFY(connect(m_mainWindow.get(), &MainWindow::error, this, &GlobalController::onError));

	VERIFY(connect(m_mainWindow.get(), &MainWindow::logIn, m_requester, &Requester::onLogIn));
	VERIFY(connect(m_requester, &Requester::logInResponse, m_mainWindow.get(), &MainWindow::onLogInResponse));
	VERIFY(connect(m_requester, &Requester::logInResponse, m_lastMessagesModel, &LastMessagesModel::onLogInResponse));

	VERIFY(connect(m_mainWindow.get(), &MainWindow::signUp, m_requester, &Requester::onSignUp));
	VERIFY(connect(m_requester, &Requester::signUpResponse, m_mainWindow.get(), &MainWindow::onSignUpResponse));

	VERIFY(connect(m_lastMessagesModel, &LastMessagesModel::getLastMessages, m_requester, &Requester::onGetLastMessages));
	VERIFY(connect(m_requester, &Requester::getLastMessagesResponse, m_lastMessagesModel, &LastMessagesModel::onGetLastMessagesResponse));

	VERIFY(connect(m_messagesModel, &MessagesModel::getMessages, m_requester, &Requester::onGetMessages));
	VERIFY(connect(m_requester, &Requester::getMessagesResponse, m_messagesModel, &MessagesModel::onGetMessagesResponse));

	VERIFY(connect(m_messagesModel, &MessagesModel::sendMessages, m_requester, &Requester::onSendMessages));
	VERIFY(connect(m_requester, &Requester::sendMessagesResponse, m_messagesModel, &MessagesModel::onSendMessagesResponse));

	VERIFY(connect(m_requester, &Requester::newMessage, m_lastMessagesModel, &LastMessagesModel::onNewMessage));
	VERIFY(connect(m_requester, &Requester::newMessage, m_messagesModel, &MessagesModel::onNewMessage));

	VERIFY(connect(m_requester, &Requester::connected, m_mainWindow.get(), &MainWindow::onConnected));

	m_requesterThread->start();
	ASSERT(m_requesterThread->isRunning());
}

GlobalController::~GlobalController()
{
	m_requesterThread->quit();
	m_requesterThread->wait();
}

void Controllers::GlobalController::run()
{
	m_mainWindow->show();
}

void GlobalController::onError(const QString& error)
{
	m_mainWindow->showError(error);
	//QMessageBox::critical(nullptr, "Error", error);
}
