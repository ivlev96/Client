#include "requester.h"
#include "authorization/authorizationinfo.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractSocket>

using namespace Network;

Requester::Requester(const QUrl& serverUrl, QObject* parent)
	: QObject(parent)
	, m_serverUrl(serverUrl)
	, m_socket(new QWebSocket())
{
	qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");
	assert(connect(m_socket, &QWebSocket::connected, this, &Requester::connected));
	assert(connect(m_socket, &QWebSocket::disconnected, this, &Requester::onDisconnected));
	assert(connect(m_socket, qOverload<QAbstractSocket::SocketError>(&QWebSocket::error), this, &Requester::onError));
	assert(connect(m_socket, &QWebSocket::textMessageReceived, this, &Requester::onMessageReceived));

	m_socket->open(m_serverUrl);
}

void Requester::onDisconnected()
{
}

void Requester::onError(QAbstractSocket::SocketError)
{
	emit error(m_socket->errorString());
}

void Requester::onMessageReceived(const QString& message)
{
	QJsonParseError error;
	const QJsonDocument doc = QJsonDocument::fromJson(QByteArray().append(message), &error);
	assert(error.error == QJsonParseError::NoError);

	const QJsonObject json(doc.object());
	assert(!json[Common::typeField].isNull());

	const QString type = json[Common::typeField].toString();

	if (type == Common::sendMessagesResponse)
	{
		const Common::SendMessagesResponse response(json);
		emit sendMessagesResponse(response.messages, response.state);
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
			return;
		}

		emit getMessagesResponse(otherId, response.messages);
		return;
	}

	assert(!"Not implemented");
}

void Requester::onGetMessages(int otherId, int count)
{
	const int myId = Authorization::AuthorizationInfo::instance().id();
	const QJsonObject json = Common::GetMessagesRequest(myId, otherId, count).toJson();
	const QJsonDocument doc(json);

	sendMessage(doc.toJson());
}

void Requester::onSendMessage(const Common::Person& other, const QString& message)
{
	const Common::Person me = Authorization::AuthorizationInfo::instance().person();
	const QJsonObject json = Common::SendMessagesRequest({ Common::Message(me, other, QDateTime::currentDateTime(), message) }).toJson();
	const QJsonDocument doc(json);

	sendMessage(doc.toJson());
}

void Requester::sendMessage(const QString& message) const
{
	assert(m_socket->isValid());
	m_socket->sendTextMessage(message);
	m_socket->flush();
}
