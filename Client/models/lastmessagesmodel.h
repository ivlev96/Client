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

	Common::Person personByRow(int row) const;

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
	void getLastMessages(int count, const std::optional<Common::MessageIdType>& from = {});

public slots:
	void onLogInResponse();

	void onGetLastMessagesResponse(Common::PersonIdType id,
		const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages,
		const std::optional<Common::MessageIdType>& before);

	void onNewMessage(const Common::Person& from, const Common::Message& message);

private:
	void pushFrontMessages(const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages);
	void pushBackMessages(const std::vector<std::pair<Common::Person, Common::Message>>& lastMessages, Common::MessageIdType before);

private:
	std::deque<std::pair<Common::Person, Common::Message>> m_messages;
};

}