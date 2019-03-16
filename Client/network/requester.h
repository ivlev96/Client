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
	void logInResponse(const std::optional<Common::Person>& person);
	void signUpResponse(const std::optional<Common::Person>& person);
	
	void getLastMessagesResponse(Common::PersonIdType id, 
		const std::vector<std::pair<Common::Person, Common::Message>>& messages, 
		const std::optional<Common::MessageIdType>& before);
	
	void sendMessagesResponse(const std::vector<Common::Message>& messages);

	void getMessagesResponse(Common::PersonIdType otherId, 
		const std::vector<Common::Message>& messages, 
		const std::optional<Common::MessageIdType>& before);

	void newMessage(const Common::Person& from, const Common::Message& message);

	void error(const QString& error);
	void connected();

public slots:
	void onThreadStarted();

	void onConnected();
	void onDisconnected();
	void onError(QAbstractSocket::SocketError error);
	void onMessageReceived(const QString& message);

	void onLogIn(const QString& login, const QString& password);
	void onSignUp(
		const QString& firstName,
		const QString& lastName,
		const QString& avatarUrl,
		const QString& login,
		const QString& password);

	void onGetMessages(Common::PersonIdType otherId, int count, 
		const std::optional<Common::MessageIdType>& before = {});

	void onGetLastMessages(int count, const std::optional<Common::MessageIdType>& before = {});
	void onSendMessages(const std::vector<Common::Message>& messages);

private:
	void sendMessage(const QJsonObject& json);

private:
	QUrl m_serverUrl;
	std::unique_ptr<QWebSocket> m_socket;

	std::queue<QJsonObject> m_pendingMessages;
};

}