#pragma once

#include "common/message.h"
#include "common/person.h"

namespace Models
{

class LastMessagesModel : public QAbstractListModel
{
	Q_OBJECT

public:
	LastMessagesModel(QObject *parent = nullptr);
	~LastMessagesModel();

	Common::Person personByIndex(const QModelIndex& index) const;

	//QAbstractItemModel implementation:
	bool hasIndex(int row, int column, const QModelIndex& parent = {}) const;
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
	virtual QModelIndex parent(const QModelIndex& child) const override;

	virtual int rowCount(const QModelIndex& parent = {}) const override;
	virtual int columnCount(const QModelIndex& parent = {}) const override;
	virtual bool hasChildren(const QModelIndex& parent = {}) const override;

	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	virtual QHash<int, QByteArray> roleNames() const override;

signals:
	void personSelected(const Common::Person& other);

public slots:
	void insertMessages(Common::PersonIdType id, bool isNew, const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages);
	void updateOne(const std::pair<Common::Person, Common::Message>& last);

private:
	void pushFrontMessages(const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages);
	void pushBackMessages(const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages);

private:
	std::deque<std::pair<Common::Person, Common::Message>> m_messages;
};

}