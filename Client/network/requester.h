#pragma once
#include "common/common.h"
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
	void sendMessageResponse(const Common::Message& message, Common::State state);
	void getMessagesResponse(int otherId, const std::vector<Common::Message>& messages);


public slots:
	void onConnected();
	void onDisconnected();
	void onMessageReceived(const QString& message);

	void getMessages(int otherId, int count);

private:
	QUrl m_serverUrl;
	QWebSocket* m_socket;
};

}