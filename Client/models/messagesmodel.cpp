#include "messagesmodel.h"
#include "authorization/authorizationinfo.h"

#include <QUrl>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <tuple>

using namespace Models;

MessagesModel::MessagesModel(QObject *parent)
	: QAbstractListModel(parent)
{
	QFile debugMessages("debugMessages.json");
	if (!debugMessages.exists())
	{
		debugGenerate();
	}

	assert(debugMessages.open(QFile::ReadOnly | QFile::Text));
	pushBackMessages(debugMessages.readAll());
	debugMessages.close();
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
		return { m_messages[index.row()].nameFrom };

	case MessagesDataRole::MessageTimeRole:
		{
			auto dateTime = m_messages[index.row()].dateTime;
			if (dateTime.date() == QDate::currentDate())
			{
				return { dateTime.time().toString("hh:mm:ss") };
			}
			return { dateTime.toString("dd.MM.yy hh:mm:ss") };
		}

	case MessagesDataRole::MessageAvatarRole:
		return { m_messages[index.row()].avatar };

	case MessagesDataRole::MessageIsFromMeRole:
		return { m_messages[index.row()].idFrom == Authorization::AuthorizationInfo::instance().id() };

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

void MessagesModel::pushFrontMessages(const QByteArray& json)
{
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(json, &error);
	assert(error.error == QJsonParseError::NoError);
	assert(doc.isArray());

	QJsonArray array = doc.array();
	std::vector<Message> newMessages(array.size());

	std::transform(array.constBegin(), array.constEnd(), newMessages.begin(),
		[](const QJsonValue& json) 
		{
			assert(json.isObject()); 
			return Message(json.toObject()); 
		});

	std::copy(newMessages.crbegin(), newMessages.crend(), std::front_inserter(m_messages));
}

void MessagesModel::pushBackMessages(const QByteArray& json)
{
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(json, &error);
	assert(error.error == QJsonParseError::NoError);
	assert(doc.isArray());

	QJsonArray array = doc.array();
	std::transform(array.constBegin(), array.constEnd(), std::back_inserter(m_messages),
		[](const QJsonValue& json)
	{
		assert(json.isObject());
		return Message(json.toObject());
	});
}

void MessagesModel::debugGenerate()
{
	std::vector<std::tuple<QString, QString, QUrl>> idNameAvatar
	{
		{ "1", "Ivan Ivlev", QUrl::fromLocalFile("Vanya.jpg") },
		{ "2", "Pavel Zharov", QUrl::fromLocalFile("Pasha.jpg") }
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
				time = time.addSecs(60 * (random%4 + 1)),
				std::get<0>(idNameAvatar[random%2]),
				std::get<0>(idNameAvatar[1 - random%2]),
				std::get<1>(idNameAvatar[random % 2]),
				std::get<1>(idNameAvatar[1 - random % 2]),
				text[random % text.size()],
				std::get<2>(idNameAvatar[random % 2])
			).toJson()
		);
	}
	QJsonDocument doc(jsonArray);
	QFile debugMessages("debugMessages.json");
	assert(debugMessages.open(QFile::WriteOnly));

	debugMessages.write(doc.toJson());
	debugMessages.close();
}
