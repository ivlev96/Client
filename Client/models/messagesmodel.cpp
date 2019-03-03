#include "messagesmodel.h"
#include "modelscommon.h"
#include "authorization/authorizationinfo.h"
#include "common/common.h"

using namespace Models;

MessagesModel::MessagesModel(QObject *parent)
	: QAbstractListModel(parent)
	, m_isWaitForResponse(false)
	, m_timer(new QTimer(this))
	, m_otherPerson()
{
	m_timer->setSingleShot(true);
	VERIFY(connect(m_timer, &QTimer::timeout, this, &MessagesModel::stopWaiting));

	QFile savedMessages;
	QFile savedPersons;

	savedMessages.setFileName("savedMessages.json");
	savedPersons.setFileName("savedPersons.json");

	if (savedMessages.exists())
	{
		ASSERT(savedMessages.open(QFile::ReadOnly | QFile::Text));

		QJsonParseError error;
		QJsonDocument doc = QJsonDocument::fromJson(savedMessages.readAll(), &error);
		ASSERT(error.error == QJsonParseError::NoError);
		ASSERT(doc.isArray());

		QJsonArray array = doc.array();
		std::transform(array.constBegin(), array.constEnd(), std::back_inserter(m_messages),
			[](const QJsonValue& json)
		{
			ASSERT(json.isObject());
			return Common::Message(json.toObject());
		});

		savedMessages.close();
	}

	if (savedPersons.exists())
	{
		ASSERT(savedPersons.open(QFile::ReadOnly | QFile::Text));

		QJsonParseError error;
		QJsonDocument doc = QJsonDocument::fromJson(savedPersons.readAll(), &error);
		ASSERT(error.error == QJsonParseError::NoError);
		ASSERT(doc.isArray());

		QJsonArray array = doc.array();
		std::transform(array.constBegin(), array.constEnd(), std::inserter(m_person, m_person.begin()),
			[](const QJsonValue& json)
		{
			ASSERT(json.isObject());
			const Common::Person person(json.toObject());
			return std::make_pair(person.id, person);
		});

		savedPersons.close();
	}
}

MessagesModel::~MessagesModel()
{

}

Common::Person MessagesModel::otherPerson() const
{
	return m_otherPerson;
}

void MessagesModel::addNewMessage(const QString& text)
{
	Common::Person me = Authorization::AuthorizationInfo::instance().person();

	const std::vector<Common::Message> newMessages(1, { me.id, otherPerson().id, QDateTime::currentDateTime(), text });

	pushBackMessages(newMessages);
	emit sendMessages(newMessages);
}

bool MessagesModel::hasIndex(int row, int column, const QModelIndex &parent) const
{
	return !parent.isValid() && column == 0 && 
		row >= 0 && row < m_messages.size();
}

QModelIndex MessagesModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	ASSERT(!parent.isValid());

	return createIndex(row, column, static_cast<quintptr>(0));
}

QModelIndex MessagesModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	ASSERT(child.isValid());

	return {};
}

int MessagesModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	ASSERT(!parent.isValid());

	return static_cast<int>(m_messages.size());
}

int MessagesModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	ASSERT(!parent.isValid());

	return 1;
}

bool MessagesModel::hasChildren(const QModelIndex& parent) const
{
	return !parent.isValid() && rowCount(parent) > 0;
}

QVariant MessagesModel::data(const QModelIndex& index, int role) const
{
	ASSERT(hasIndex(index.row(), index.column(), index.parent()));
	ASSERT(m_person.count(m_messages[index.row()].from) == 1);

	const auto personFrom = m_person.at(m_messages[index.row()].from);

	switch (role)
	{
	case Qt::DisplayRole:
		return { m_messages[index.row()].text };

	case MessagesDataRole::MessageAuthorRole:
		return { personFrom.name() };

	case MessagesDataRole::MessageTimeRole:
		{
			const auto dateTime = m_messages[index.row()].dateTime;
			if (dateTime.date() == QDate::currentDate())
			{
				return { dateTime.time().toString(Common::timeFormat) };
			}
			return { dateTime.toString(Common::dateTimeFormat) };
		}

	case MessagesDataRole::MessageAvatarRole:
		return { personFrom.avatarUrl };

	case MessagesDataRole::MessageIsFromMeRole:
		return { personFrom.id == Authorization::AuthorizationInfo::instance().id() };

	case MessagesDataRole::MessageStateRole:
		return { static_cast<int>(m_messages[index.row()].state) };

	default: 
		return {};
	}
}

bool MessagesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	Q_UNUSED(index);
	Q_UNUSED(value);
	Q_UNUSED(role);

	return false;
}

QHash<int, QByteArray> MessagesModel::roleNames() const
{
	return Models::roleNames();
}

void MessagesModel::setPerson(const Common::Person& person)
{
	if (person != m_otherPerson)
	{
		beginResetModel();
		m_otherPerson = person;

		m_person.clear();
		const auto me = Authorization::AuthorizationInfo::instance().person();
		m_person[me.id] = me;
		m_person[m_otherPerson.id] = m_otherPerson;

		m_messages.clear();
		endResetModel();

		emit getMessages(m_otherPerson.id, Common::defaultMessagesCount);

		startWaiting();	
	}
}

void MessagesModel::startWaiting()
{
	m_isWaitForResponse = true;
	m_timer->start(Common::defaultTimeot);
}

void MessagesModel::stopWaiting()
{
	if (m_isWaitForResponse)
	{
		m_isWaitForResponse = false;
		emit error("No answer from the server");
	}
}

void MessagesModel::onSendMessagesResponse(const std::vector<Common::Message>& messages)
{
	//update states of this messages
	Q_UNUSED(messages);
}

void MessagesModel::onGetMessagesResponse(Common::PersonIdType otherId,
	const std::vector<Common::Message>& messages,
	const std::optional<Common::MessageIdType>& before)
{
	m_isWaitForResponse = false;

	Q_UNUSED(otherId);
	ASSERT(otherId == m_otherPerson.id);
	ASSERT(messages.size() > 0);

	if (before.has_value())
	{
		pushFrontMessages(messages, *before);
	}
	else
	{
		pushBackMessages(messages);
	}
}

void MessagesModel::onNewMessage(const Common::Person& from, const Common::Message& message)
{
	if (from.id == m_otherPerson.id)
	{
		pushBackMessages({ message });
	}
}

void MessagesModel::pushFrontMessages(const std::vector<Common::Message>& newMessages, Common::MessageIdType before)
{
	auto it = std::find_if(m_messages.begin(), m_messages.end(), 
		[&before](const auto& message)
		{
			return message.id == before;
		});
	ASSERT(it != m_messages.end());

	const int row = static_cast<int>(std::distance(m_messages.begin(), it));

	beginInsertRows(QModelIndex(), row, row + static_cast<int>(newMessages.size()) - 1);
	m_messages.insert(it, newMessages.cbegin(), newMessages.cend());
	endInsertRows();
}

void MessagesModel::pushBackMessages(const std::vector<Common::Message>& newMessages)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount() + static_cast<int>(newMessages.size()) - 1);
	std::copy(newMessages.cbegin(), newMessages.cend(), std::back_inserter(m_messages));
	endInsertRows();

	emit scrollTo(rowCount() - 1);
}

void MessagesModel::debugGenerate()
{
	std::vector<Common::Person> persons
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
			Common::Message(
				persons[random % 2].id,
				persons[1 - random % 2].id,
				time = time.addSecs(60 * (random % 4 + 1)),
				text[random % text.size()]
			).toJson()
		);
	}

	QJsonDocument doc(jsonArray);
	QFile debugMessages("debugMessages.json");
	ASSERT(debugMessages.open(QFile::WriteOnly));
	debugMessages.write(doc.toJson());
	debugMessages.close();

	QJsonArray jsonPersons
	{
		persons[0].toJson(),
		persons[1].toJson()
	};

	doc.setArray(jsonPersons);
	QFile debugPersons("debugPersons.json");
	ASSERT(debugPersons.open(QFile::WriteOnly));
	debugPersons.write(doc.toJson());
	debugPersons.close();
}

void MessagesModel::saveMessages() const
{
	QJsonArray messages;

	std::transform(m_messages.cbegin(), m_messages.cend(), std::back_inserter(messages),
		[](const Common::Message& message)
		{
			return message.toJson();
		});

	QJsonDocument doc(messages);
	QFile savedMessages("savedMessages.json");
	ASSERT(savedMessages.open(QFile::WriteOnly));
	savedMessages.write(doc.toJson());
	savedMessages.close();
}

void MessagesModel::savePersons() const
{
	QJsonArray persons;

	std::transform(m_person.cbegin(), m_person.cend(), std::back_inserter(persons),
		[](const auto& pair)
	{
		return pair.second.toJson();
	});

	QJsonDocument doc(persons);
	QFile savedPersons("savedPersons.json");
	ASSERT(savedPersons.open(QFile::WriteOnly));
	savedPersons.write(doc.toJson());
	savedPersons.close();
}
