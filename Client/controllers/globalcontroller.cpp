#include "globalcontroller.h"
#include "common/common.h"

#include <QMessageBox>

using namespace Controllers;
using namespace Widgets;
using namespace Models;
using namespace Network;

GlobalController::GlobalController()
	: m_messagesModel(new MessagesModel(this))
	, m_requester(new Requester(Common::serverUrl))
	, m_requesterThread(new QThread(this))
{
	qRegisterMetaType<Common::Person>("Person");
	qRegisterMetaType<Common::PersonIdType>("Common::PersonIdType");

	qRegisterMetaType<Common::Message>("Message");
	qRegisterMetaType<Common::MessageIdType>("Common::MessageIdType");
	qRegisterMetaType<std::vector<Common::Message>>("vector<Message>");
	qRegisterMetaType<Common::Message::State>("State");

	m_mainWindow = new MainWindow(m_messagesModel);

	m_requester->moveToThread(m_requesterThread);
	assert(connect(m_requesterThread, &QThread::finished, m_requester, &QObject::deleteLater));
	assert(connect(m_requesterThread, &QThread::started, m_requester, &Requester::onThreadStarted));

	assert(connect(m_requester, &Requester::error, this, &GlobalController::onError));
	assert(connect(m_messagesModel, &MessagesModel::error, this, &GlobalController::onError));

	assert(connect(m_messagesModel, &MessagesModel::getMessages, m_requester, &Requester::onGetMessages));
	assert(connect(m_requester, &Requester::getMessagesResponse, m_messagesModel, &MessagesModel::onGetMessagesResponse));

	assert(connect(m_messagesModel, &MessagesModel::sendMessages, m_requester, &Requester::onSendMessages));
	assert(connect(m_requester, &Requester::sendMessagesResponse, m_messagesModel, &MessagesModel::onSendMessagesResponse));

	assert(connect(m_requester, &Requester::connected, m_mainWindow, &MainWindow::onConnected));

	m_requesterThread->start();
	assert(m_requesterThread->isRunning());
}

GlobalController::~GlobalController()
{
	m_requesterThread->quit();
	m_requesterThread->wait();
	delete m_mainWindow;
}

void Controllers::GlobalController::run()
{
	m_mainWindow->show();
}

void GlobalController::onError(const QString& error)
{
	QMessageBox::critical(nullptr, "Error", error);
}
