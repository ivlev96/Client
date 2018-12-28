#pragma once
#include <QAbstractListModel>
#include "message.h"

namespace Models
{

enum MessagesDataRole
{
	MessageAuthorRole = 0x101,
	MessageTimeRole,
	MessageAvatarRole
};

class MessagesModel : public QAbstractListModel
{
	Q_OBJECT

public:
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

private:
	std::vector<Message> m_messages;

};

}