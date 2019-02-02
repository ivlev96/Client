#pragma once
#include "common/common.h"
#include "common/person.h"
#include "common/message.h"
#include "common/commands.h"

#include <QObject>
#include <QUrl>
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>
#include <vector>

namespace Network
{

class Requester : public QObject
{
	Q_OBJECT

public:
	explicit Requester(const QUrl& serverUrl = Common::serverUrl, QObject* parent = nullptr);

signals:
	void sendMessagesResponse(const std::vector<Common::Message>& message, Common::State state);
	void getMessagesResponse(int otherId, const std::vector<Common::Message>& messages);
	void error(const QString& error);
	void connected();

public slots:
	void onDisconnected();
	void onError(QAbstractSocket::SocketError error);
	void onMessageReceived(const QString& message);

	void onGetMessages(int otherId, int count);
	void onSendMessage(const Common::Person& other, const QString& message);

private:
	void sendMessage(const QString& message) const;

private:
	QUrl m_serverUrl;
	QWebSocket* m_socket;
};

}