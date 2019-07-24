#pragma once

namespace Models
{
	class MessagesModel;
	class LastMessagesModel;
	class LastMessagesProxyModel;
	class PossibleFriendsModel;
}

namespace Network
{
	class Requester;
}

namespace Widgets
{
	class MainWindow;
}

namespace Controllers
{

class GlobalController : public QObject
{
	Q_OBJECT

public:
	GlobalController();
	~GlobalController();

public slots:
	void onError(const QString& error);
	void onPersonSelected(int row);
	void onPosibleFriendSelected(int row);

private:
	std::unique_ptr<Widgets::MainWindow> m_mainWindow;

	Models::MessagesModel* m_messagesModel;
	Models::LastMessagesModel* m_lastMessagesModel;
	Models::LastMessagesProxyModel* m_lastMessagesProxyModel;
	Models::PossibleFriendsModel* m_possibleFriendsModel;

	Network::Requester* m_requester;

	QThread* m_requesterThread;
};

}