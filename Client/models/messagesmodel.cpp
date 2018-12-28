#include "messagesmodel.h"

using namespace Models;

MessagesModel::MessagesModel(QObject *parent)
	: QAbstractListModel(parent)
	, m_messages
	{
		{ QDateTime(QDate::currentDate(), QTime::currentTime()), "111", "Ivan Ivlev", "Mewssage", MessageAuthor::Me },
		{ QDateTime(QDate::currentDate().addDays(1), QTime::currentTime()), "111", "Pavel Zharov", "Answer", MessageAuthor::Other }
	}
{

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
		return { m_messages[index.row()].name };

	case MessagesDataRole::MessageTimeRole:
		return { m_messages[index.row()].dateTime };

	case MessagesDataRole::MessageAvatarRole:
		return { m_messages[index.row()].avatar };

	default: 
		return {};
	}
}

bool MessagesModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	return false;
}
