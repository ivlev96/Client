#include "messagesmodel.h"
#include "authorization/authorizationinfo.h"
#include "common/common.h"

#include <QUrl>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <tuple>

using namespace Models;
using namespace Common;

MessagesModel::MessagesModel(QObject *parent)
	: QAbstractListModel(parent)
	, m_isWaitForResponce(false)
	, m_timer(new QTimer(this))
{
	m_timer->setSingleShot(true);
	assert(connect(m_timer, &QTimer::timeout, this, &MessagesModel::stopWaiting));

	QFile savedMessages;

#ifdef _DEBUG

	savedMessages.setFileName("debugMessages.json");
	if (!savedMessages.exists())
	{
		debugGenerate();
	}

#else

	savedMessages.setFileName("savedMessages.json");
	if (!savedMessages.exists())
	{
		return;
	}

#endif

	assert(savedMessages.open(QFile::ReadOnly | QFile::Text));

	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(savedMessages.readAll(), &error);
	assert(error.error == QJsonParseError::NoError);
	assert(doc.isArray());

	QJsonArray array = doc.array();
	std::transform(array.constBegin(), array.constEnd(), std::back_inserter(m_messages),
		[](const QJsonValue& json)
	{
		assert(json.isObject());
		return Message(json.toObject());
	});

	savedMessages.close();
}

MessagesModel::~MessagesModel()
{

}

bool MessagesModel::hasIndex(int row, int column, const QModelIndex &parent) const
{
	return !parent.isValid() && column == 0 && 
		row >= 0 && row < m_messages.size();
}

QModelIndex MessagesModel::index(int row, int column, const QModelIndex& parent) const
{
	assert(!parent.isValid());

	return createIndex(row, column, static_cast<quintptr>(0));
}

QModelIndex MessagesModel::parent(const QModelIndex& child) const
{
	assert(child.isValid());

	return {};
}

int MessagesModel::rowCount(const QModelIndex& parent) const
{
	assert(!parent.isValid());

	return static_cast<int>(m_messages.size());
}

int MessagesModel::columnCount(const QModelIndex& parent) const
{
	assert(!parent.isValid());

	return 1;
}

bool MessagesModel::hasChildren(const QModelIndex& parent) const
{
	return !parent.isValid() && rowCount(parent) > 0;
}

QVariant MessagesModel::data(const QModelIndex& index, int role) const
{
	assert(hasIndex(index.row(), index.column(), index.parent()));

	switch (role)
	{
	case Qt::DisplayRole:
		return { m_messages[index.row()].text };

	case MessagesDataRole::MessageAuthorRole:
		return { m_messages[index.row()].from.name() };

	case MessagesDataRole::MessageTimeRole:
		{
			auto dateTime = m_messages[index.row()].dateTime;
			if (dateTime.date() == QDate::currentDate())
			{
				return { dateTime.time().toString("hh:mm:ss") };
			}
			return { dateTime.toString(Common::dateTimeFormat) };
		}

	case MessagesDataRole::MessageAvatarRole:
		return { m_messages[index.row()].from.avatarUrl };

	case MessagesDataRole::MessageIsFromMeRole:
		return { m_messages[index.row()].from.id == Authorization::AuthorizationInfo::instance().id() };

	default: 
		return {};
	}
}

bool MessagesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	return false;
}

QHash<int, QByteArray> MessagesModel::roleNames() const
{
	return
	{
		{ Qt::DisplayRole, "messageText" },
		{ MessagesDataRole::MessageAuthorRole, "messageName" },
		{ MessagesDataRole::MessageTimeRole, "messageTime" },
		{ MessagesDataRole::MessageAvatarRole, "messageAvatar" },
		{ MessagesDataRole::MessageIsFromMeRole, "messageIsFromMe" }
	};
}

void MessagesModel::setPerson(const Person& person)
{
	if (person != m_otherPerson)
	{
		beginResetModel();
		m_otherPerson = person;
		m_messages.clear();
		endResetModel();

		emit getMessages(m_otherPerson.id, Common::defaultMessagesCount);

		startWaiting();	
	}
}

void MessagesModel::startWaiting()
{
	m_isWaitForResponce = true;
	m_timer->start(Common::defaultTimeot);
}

void MessagesModel::stopWaiting()
{
	if (m_isWaitForResponce)
	{
		m_isWaitForResponce = false;
		emit noResponseForMessageRequest();
	}
}

void MessagesModel::onSendMessageResponse(const Message& message, State state)
{
	assert(state < State::StatesCount);
	pushBackMessages({ message });
}

void MessagesModel::onGetMessagesResponse(int otherId, const std::vector<Message>& messages)
{
	assert(otherId == m_otherPerson.id);
	pushFrontMessages(messages);
}

void MessagesModel::pushFrontMessages(const std::vector<Common::Message>& newMessages)
{
	m_messages.insert(m_messages.begin(), newMessages.cbegin(), newMessages.cend());
}

void MessagesModel::pushBackMessages(const std::vector<Common::Message>& newMessages)
{
	std::copy(newMessages.cbegin(), newMessages.cend(), std::back_inserter(m_messages));
}

void MessagesModel::debugGenerate()
{
	std::vector<Person> persons
	{
		{ 1, "Ivan", "Ivlev", QUrl::fromLocalFile("Vanya.jpg").toString() },
		{ 2, "Pavel", "Zharov", QUrl::fromLocalFile("Pasha.jpg").toString() }
	};

	std::vector<QString> text
	{
		"Hello!",
		"How are you?",
		"I love cakes",
		"Oh\nI'm fine\nThank you",
		"Ololo\n\n\nPyschPysch\n\n!!!",
	};


	srand(time(0));
	QJsonArray jsonArray;

	QDateTime time = QDateTime::currentDateTime();

	for (int i = 0; i < 1000; ++i)
	{
		const int random = rand();
		jsonArray.push_back(
			Message(
				persons[random % 2],
				persons[1 - random % 2],
				time = time.addSecs(60 * (random % 4 + 1)),
				text[random % text.size()]
			).toJson()
		);
	}
	QJsonDocument doc(jsonArray);
	QFile debugMessages("debugMessages.json");
	assert(debugMessages.open(QFile::WriteOnly));

	debugMessages.write(doc.toJson());
	debugMessages.close();
}
