#include "requester.h"
#include "authorization/authorizationinfo.h"
#include "common/commands.h"
#include <QJsonObject>
#include <QJsonDocument>

using namespace Network;

Requester::Requester(const QUrl& serverUrl, QObject* parent)
	: QObject(parent)
	, m_serverUrl(serverUrl)
	, m_socket(new QWebSocket())
{
	assert(connect(m_socket, &QWebSocket::connected, this, &Requester::onConnected));
	assert(connect(m_socket, &QWebSocket::disconnected, this, &Requester::onDisconnected));
	assert(connect(m_socket, &QWebSocket::textMessageReceived, this, &Requester::onMessageReceived));

	m_socket->open(m_serverUrl);
}

void Requester::onConnected()
{
}

void Requester::onDisconnected()
{
}

void Requester::onMessageReceived(const QString& message)
{
	QJsonParseError error;
	const QJsonDocument doc = QJsonDocument::fromJson(QByteArray().append(message), &error);
	assert(error.error == QJsonParseError::NoError);

	const QJsonObject json(doc.object());
	assert(!json[Common::typeField].isNull());

	const QString type = json[Common::typeField].toString();

	if (type == Common::sendMessageResponse)
	{
		const Common::SendMessageResponse response(json);
		emit sendMessageResponse(response.message, response.state);
		return;
	}

	if (type == Common::getMessagesResponse)
	{
		const Common::GetMessagesResponse response(json);
		const int myId = Authorization::AuthorizationInfo::instance().id();
		int otherId;

		if (response.id1 == myId)
		{
			otherId = response.id2;
		}
		else if (response.id2 == myId)
		{
			otherId = response.id1;
		}
		else
		{
			assert(!"Incorrect ids in command");
		}

		emit getMessagesResponse(otherId, response.messages);
		return;
	}
}

void Requester::getMessages(int otherId, int count)
{
	const int myId = Authorization::AuthorizationInfo::instance().id();
	const QJsonObject json = Common::GetMessagesRequest(myId, otherId, count).toJson();
	const QJsonDocument doc(json);

	m_socket->sendTextMessage(doc.toJson());
}
