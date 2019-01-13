#pragma once
#include "message.h"
#include <QAbstractListModel>
#include <deque>

namespace Models
{

class MessagesModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum MessagesDataRole
	{
		MessageAuthorRole = Qt::UserRole + 1,
		MessageTimeRole,
		MessageAvatarRole,
		MessageIsFromMeRole
	};

	explicit MessagesModel(QObject *parent = nullptr);
	~MessagesModel();

	bool hasIndex(int row, int column, const QModelIndex &parent = {}) const;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
	virtual QModelIndex parent(const QModelIndex &child) const override;

	virtual int rowCount(const QModelIndex &parent = {}) const override;
	virtual int columnCount(const QModelIndex &parent = {}) const override;
	virtual bool hasChildren(const QModelIndex &parent = {}) const override;

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

	virtual QHash<int, QByteArray> roleNames() const override;

private:
	void pushFrontMessages(const QByteArray& json);
	void pushBackMessages(const QByteArray& json);
	void debugGenerate();

private:
	std::deque<Message> m_messages;

};

}