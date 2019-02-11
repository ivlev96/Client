#pragma once
#include "common/common.h"
#include "common/person.h"
#include "common/message.h"
#include "common/commands.h"

namespace Network
{

class Requester : public QObject
{
	Q_OBJECT

public:
	explicit Requester(const QUrl& serverUrl = Common::serverUrl, QObject* parent = nullptr);
	~Requester();

signals:
	void sendMessagesResponse(const std::vector<Common::Message>& message, Common::Message::State state);
	void getMessagesResponse(Common::PersonIdType otherId, bool isNew, const std::vector<Common::Message>& messages);
	void error(const QString& error);
	void connected();

public slots:
	void onThreadStarted();

	void onConnected();
	void onDisconnected();
	void onError(QAbstractSocket::SocketError error);
	void onMessageReceived(const QString& message);

	void onGetMessages(Common::PersonIdType otherId, bool isNew, int count);
	void onSendMessages(const std::vector<Common::Message>& messages);

private:
	void sendMessage(const QString& message);

private:
	QUrl m_serverUrl;
	QWebSocket* m_socket;

	std::queue<QString> m_pendingMessages;
};

}