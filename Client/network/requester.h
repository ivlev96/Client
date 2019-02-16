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
	void logInResponse(bool ok, const std::optional<Common::Person>& person);
	void error(const QString& error);
	void connected();

public slots:
	void onThreadStarted();

	void onConnected();
	void onDisconnected();
	void onError(QAbstractSocket::SocketError error);
	void onMessageReceived(const QString& message);

	void onLogIn(const QString& login, const QString& password);

	void onGetMessages(Common::PersonIdType otherId, bool isNew, int count);
	void onSendMessages(const std::vector<Common::Message>& messages);

private:
	void sendMessage(const QJsonObject& json);

private:
	QUrl m_serverUrl;
	std::unique_ptr<QWebSocket> m_socket;

	std::queue<QJsonObject> m_pendingMessages;
};

}