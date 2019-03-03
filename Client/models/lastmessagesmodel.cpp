#include "lastmessagesmodel.h"
#include "modelscommon.h"
#include "authorization/authorizationinfo.h"
#include "common/common.h"

using namespace Models;

LastMessagesModel::LastMessagesModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

LastMessagesModel::~LastMessagesModel()
{
}

Common::Person Models::LastMessagesModel::personByRow(int row) const
{
	ASSERT(row < rowCount());
	return m_messages[row].first;
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
	ASSERT(hasIndex(row, column, parent));
	return createIndex(row, column, static_cast<quintptr>(0));
}

QModelIndex LastMessagesModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	ASSERT(child.isValid());

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
	ASSERT(!parent.isValid());

	return 1;
}

bool LastMessagesModel::hasChildren(const QModelIndex& parent) const
{
	return !parent.isValid() && rowCount(parent) > 0;
}

QVariant LastMessagesModel::data(const QModelIndex& index, int role) const
{
	ASSERT(hasIndex(index.row(), index.column(), index.parent()));

	const auto me = Authorization::AuthorizationInfo::instance().id();
	const auto[person, message] = m_messages[index.row()];

	switch (role)
	{
	case Qt::DisplayRole:
		return message.text.simplified();
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

void LastMessagesModel::onLogInResponse()
{
	emit getLastMessages(Common::defaultMessagesCount);
}

void LastMessagesModel::onGetLastMessagesResponse(Common::PersonIdType id,
	const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages,
	const std::optional<Common::MessageIdType>& before)
{
	Q_UNUSED(id);
	ASSERT(id == Authorization::AuthorizationInfo::instance().id());

	if (!before.has_value())
	{
		pushFrontMessages(lastMessages);
	}
	else
	{
		pushBackMessages(lastMessages, *before);
	}
}

void LastMessagesModel::onNewMessage(const Common::Person& from, const Common::Message& message)
{
	const auto it = std::find_if(m_messages.rbegin(), m_messages.rend(),
		[&from](const auto pair)
	{
		return pair.first == from;
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
	m_messages.emplace_front(from, message);
	endInsertRows();
}

void LastMessagesModel::pushFrontMessages(const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages)
{
	beginInsertRows({}, 0, static_cast<int>(lastMessages.size()) - 1);
	m_messages.insert(m_messages.begin(), lastMessages.cbegin(), lastMessages.cend());
	endInsertRows();
}

void LastMessagesModel::pushBackMessages(const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages, Common::MessageIdType before)
{
	Q_UNUSED(before);
	ASSERT(before == m_messages.rbegin()->second.id);

	beginInsertRows({}, rowCount(), rowCount() + static_cast<int>(lastMessages.size()) - 1);
	std::copy(lastMessages.cbegin(), lastMessages.cend(), std::back_inserter(m_messages));
	endInsertRows();
}