#include "lastmessagesmodel.h"
#include "modelscommon.h"
#include "authorization/authorizationinfo.h"
#include "common/common.h"

using namespace Models;

LastMessagesModel::LastMessagesModel(QObject *parent)
	: QAbstractListModel(parent)
{
#ifdef _DEBUG
	debugInit();
#endif
}

LastMessagesModel::~LastMessagesModel()
{
}

Common::Person Models::LastMessagesModel::personByIndex(const QModelIndex& index) const
{
	assert(hasIndex(index.row(), index.column(), index.parent()));
	return m_messages[index.row()].first;
}

bool LastMessagesModel::hasIndex(int row, int column, const QModelIndex& parent) const
{
	return 
		!parent.isValid() &&
		row >= 0 &&
		row < rowCount(parent) &&
		column == 0;
}

QModelIndex LastMessagesModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	assert(hasIndex(row, column, parent));
	return createIndex(row, column, static_cast<quintptr>(0));
}

QModelIndex LastMessagesModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	assert(child.isValid());

	return {};
}

int LastMessagesModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return static_cast<int>(m_messages.size());
}

int LastMessagesModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	assert(!parent.isValid());

	return 1;
}

bool LastMessagesModel::hasChildren(const QModelIndex& parent) const
{
	return !parent.isValid() && rowCount(parent) > 0;
}

QVariant LastMessagesModel::data(const QModelIndex& index, int role) const
{
	assert(hasIndex(index.row(), index.column(), index.parent()));

	const auto me = Authorization::AuthorizationInfo::instance().id();
	const auto[person, message] = m_messages[index.row()];

	switch (role)
	{
	case Qt::DisplayRole:
		return message.text;

	case MessagesDataRole::MessageAuthorRole:
		return person.name();

	case MessagesDataRole::MessageShortAuthorRole:
		return message.from == me ? "You" : person.firstName;

	case MessagesDataRole::MessageTimeRole:
	{
		const auto dateTime = message.dateTime;
		if (dateTime.date() == QDate::currentDate())
		{
			return dateTime.time().toString(Common::timeFormat);
		}
		return dateTime.toString(Common::dateTimeFormat);
	}

	case MessagesDataRole::MessageAvatarRole:
		return person.avatarUrl;

	case MessagesDataRole::MessageIsFromMeRole:
		return person.id == me;

	case MessagesDataRole::MessageStateRole:
		return static_cast<int>(message.state);

	default:
		return {};
	}
}

bool LastMessagesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	Q_UNUSED(index);
	Q_UNUSED(value);
	Q_UNUSED(role);

	return false;
}

QHash<int, QByteArray> LastMessagesModel::roleNames() const
{
	return Models::roleNames();
}

void LastMessagesModel::updateOne(const std::pair<Common::Person, Common::Message>& last)
{
	const auto[person, message] = last;

	const auto it = std::find_if(m_messages.rbegin(), m_messages.rend(),
		[&person](const auto pair)
		{
			return pair.first == person;
		});

	if (it != m_messages.rend())
	{
		const int row = static_cast<int>(std::distance(m_messages.begin(), it.base()));
		const QModelIndex index = this->index(row, 0);

		it->second = message;
		emit dataChanged(index, index);

		beginMoveRows({}, row, row, {}, 0);
		std::rotate(it, it + 1, m_messages.rend());
		endMoveRows();

		return;
	}

	beginInsertRows({}, 0, 0);
	m_messages.push_front(last);
	endInsertRows();
}

#ifdef _DEBUG
void LastMessagesModel::debugInit()
{
	m_messages = 
	{
		{ { 2, "Pavel", "Zharov",  QUrl::fromLocalFile("Pasha.jpg").toString() }, { 2, 1, QDateTime::currentDateTime().addSecs(-60), "Message text 1<br><br><br>123" } },
		{ { 3, "Vityok", "Burrr",  QUrl::fromLocalFile("Vanya.jpg").toString() }, { 1, 3, QDateTime::currentDateTime().addSecs(-120), "Message text 2\n\n\n\n1234" } },
};
}
#endif

void LastMessagesModel::updateAll(const std::deque<std::pair<Common::Person, Common::Message>>& lastMessages)
{
	beginResetModel();
	m_messages = lastMessages;
	endResetModel();
}
