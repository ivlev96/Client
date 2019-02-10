#include "requester.h"
#include "authorization/authorizationinfo.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractSocket>

using namespace Network;

Requester::Requester(const QUrl& serverUrl, QObject* parent)
	: QObject(parent)
	, m_serverUrl(serverUrl)
	, m_socket(nullptr)
{

}

void Requester::onThreadStarted()
{
	m_socket = new QWebSocket();

	assert(connect(m_socket, &QWebSocket::connected, this, &Requester::onConnected));
	assert(connect(m_socket, &QWebSocket::disconnected, this, &Requester::onDisconnected));
	assert(connect(m_socket, qOverload<QAbstractSocket::SocketError>(&QWebSocket::error), this, &Requester::onError));
	assert(connect(m_socket, &QWebSocket::textMessageReceived, this, &Requester::onMessageReceived));

	m_socket->open(m_serverUrl);
}

Requester::~Requester()
{
	delete m_socket;
}

void Requester::onConnected()
{
	while (!m_pendingMessages.empty())
	{
		const auto command = m_pendingMessages.front();
		m_pendingMessages.pop();
		sendMessage(command);
	}

	emit connected();
}

void Requester::onDisconnected()
{
}

void Requester::onError(QAbstractSocket::SocketError)
{
	emit error(m_socket->errorString());

	if (m_socket->error() != QAbstractSocket::SocketError::OperationError)
	{
		m_socket->open(m_serverUrl);
	}
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
		const Common::PersonIdType myId = Authorization::AuthorizationInfo::instance().id();
		Common::PersonIdType otherId;

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

		emit getMessagesResponse(otherId, response.isNew, response.messages);
		return;
	}

	assert(!"Not implemented");
}

void Requester::onGetMessages(Common::PersonIdType otherId, bool isNew, int count)
{
	const Common::PersonIdType myId = Authorization::AuthorizationInfo::instance().id();
	const QJsonObject json = Common::GetMessagesRequest(myId, otherId, isNew, count).toJson();
	const QJsonDocument doc(json);

	sendMessage(doc.toJson());
}

void Requester::onSendMessages(const std::vector<Common::Message>& messages)
{
	const Common::Person me = Authorization::AuthorizationInfo::instance().person();
	const QJsonObject json = Common::SendMessagesRequest(messages).toJson();
	const QJsonDocument doc(json);

	sendMessage(doc.toJson());
}

void Requester::sendMessage(const QString& message)
{
	if (!m_socket->isValid())
	{
		m_socket->open(m_serverUrl);
		m_pendingMessages.push(message);
		return;
	}
	m_socket->sendTextMessage(message);
	m_socket->flush();
}
