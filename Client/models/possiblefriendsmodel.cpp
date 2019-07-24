#include "possiblefriendsmodel.h"
#include "authorization/authorizationinfo.h"
#include "modelscommon.h"
#include "common/common.h"

using namespace Models;

PossibleFriendsModel::PossibleFriendsModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

PossibleFriendsModel::~PossibleFriendsModel()
{
}

Common::Person PossibleFriendsModel::personByRow(int row) const
{
	return m_persons[row].first;
}

bool PossibleFriendsModel::hasIndex(int row, int column, const QModelIndex& parent) const
{
	return
		!parent.isValid() &&
		row >= 0 &&
		row < rowCount(parent) &&
		column == 0;
}

QModelIndex PossibleFriendsModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	ASSERT(hasIndex(row, column, parent));
	return createIndex(row, column, static_cast<quintptr>(0));
}

QModelIndex PossibleFriendsModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	ASSERT(child.isValid());

	return {};
}

int PossibleFriendsModel::rowCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : static_cast<int>(m_persons.size());
}

int PossibleFriendsModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	ASSERT(!parent.isValid());

	return 1;
}

bool PossibleFriendsModel::hasChildren(const QModelIndex& parent) const
{
	return !parent.isValid() && rowCount(parent) > 0;
}

QVariant PossibleFriendsModel::data(const QModelIndex& index, int role) const
{
	ASSERT(hasIndex(index.row(), index.column(), index.parent()));

	const auto me = Authorization::AuthorizationInfo::instance().id();
	const auto[person, message] = m_persons[index.row()];

	switch (role)
	{
	case Qt::DisplayRole:
		return message ? message->text.simplified() : QVariant{};
	case MessagesDataRole::MessageAuthorRole:
		return person.name();

	case MessagesDataRole::MessageShortAuthorRole:
		return message ? 
			(message->from == me ? "You" : person.firstName) :
			QVariant{};

	case MessagesDataRole::MessageTimeRole:
	{
		if (!message)
		{
			return {};
		}

		const auto dateTime = message->dateTime;
		if (dateTime.date() == QDate::currentDate())
		{
			return dateTime.time().toString(Common::timeFormat);
		}
		return dateTime.toString(Common::dateFormat);
	}

	case MessagesDataRole::MessageAvatarRole:
		return person.avatarUrl;

	case MessagesDataRole::MessageIsFromMeRole:
		return person.id == me;

	case MessagesDataRole::MessageStateRole:
		return message ? static_cast<int>(message->state) : QVariant{};

	default:
		return {};
	}
}

QHash<int, QByteArray> PossibleFriendsModel::roleNames() const
{
	return Models::roleNames();
}

void PossibleFriendsModel::onFriendsReceived(const std::vector<std::pair<Common::Person, std::optional<Common::Message>>>& persons)
{
	beginResetModel();
	m_persons = persons;
	endResetModel();
}
