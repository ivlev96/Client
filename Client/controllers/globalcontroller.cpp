#include "globalcontroller.h"

#include "widgets/mainwindow/mainwindow.h"
#include "models/messagesmodel.h"
#include "models/lastmessagesmodel.h"
#include "models/lastmessagesproxymodel.h"
#include "models/possiblefriendsmodel.h"
#include "network/requester.h"
#include "common/common.h"

using namespace Controllers;
using namespace Widgets;
using namespace Models;
using namespace Network;

GlobalController::GlobalController()
	: m_messagesModel(new MessagesModel(this))
	, m_lastMessagesModel(new LastMessagesModel(this))
	, m_possibleFriendsModel(new PossibleFriendsModel(this))
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
	qRegisterMetaType<std::vector<std::pair<Common::Person, std::optional<Common::Message>>>>("std::vector<std::pair<Common::Person,std::optional<Common::Message>>>");

	m_lastMessagesProxyModel = new Models::LastMessagesProxyModel(this);
	m_lastMessagesProxyModel->setSourceModel(m_lastMessagesModel);

	m_mainWindow = std::make_unique<MainWindow>(m_lastMessagesProxyModel, m_messagesModel, m_possibleFriendsModel);

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

	VERIFY(connect(m_mainWindow.get(), &MainWindow::personSelected, this, &GlobalController::onPersonSelected));
	VERIFY(connect(m_mainWindow.get(), &MainWindow::possibleFriendSelected, this, &GlobalController::onPosibleFriendSelected));
	VERIFY(connect(m_mainWindow.get(), &MainWindow::sendMessage, m_messagesModel, &MessagesModel::onSendMessage));

	VERIFY(connect(m_mainWindow.get(), &MainWindow::findFriends, m_requester, &Requester::onFindFriends));
	VERIFY(connect(m_requester, &Requester::possibleFriendsList, m_possibleFriendsModel, &PossibleFriendsModel::onFriendsReceived));
	VERIFY(connect(m_mainWindow.get(), &MainWindow::filterFriendsTextChanged, m_lastMessagesProxyModel, &QSortFilterProxyModel::setFilterFixedString));

	VERIFY(connect(m_lastMessagesModel, &LastMessagesModel::getLastMessages, m_requester, &Requester::onGetLastMessages));
	VERIFY(connect(m_requester, &Requester::getLastMessagesResponse, m_lastMessagesModel, &LastMessagesModel::onGetLastMessagesResponse));

	VERIFY(connect(m_messagesModel, &MessagesModel::getMessages, m_requester, &Requester::onGetMessages));
	VERIFY(connect(m_requester, &Requester::getMessagesResponse, m_messagesModel, &MessagesModel::onGetMessagesResponse));

	VERIFY(connect(m_messagesModel, &MessagesModel::sendMessages, m_requester, &Requester::onSendMessages));
	VERIFY(connect(m_requester, &Requester::sendMessagesResponse, m_messagesModel, &MessagesModel::onSendMessagesResponse));
	VERIFY(connect(m_requester, &Requester::sendMessagesResponse, m_lastMessagesModel, &LastMessagesModel::onSuccessfullySendMessages));

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

void GlobalController::onPersonSelected(int row)
{
	m_messagesModel->setPerson(m_lastMessagesModel->personByRow(row));
}

void GlobalController::onPosibleFriendSelected(int row)
{
	m_messagesModel->setPerson(m_possibleFriendsModel->personByRow(row));
}

void GlobalController::onError(const QString& error)
{
	m_mainWindow->showError(error);
	//QMessageBox::critical(nullptr, "Error", error);
}
