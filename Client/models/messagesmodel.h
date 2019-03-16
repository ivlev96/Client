#pragma once
#include "common/message.h"
#include "common/person.h"

namespace Models
{

class MessagesModel : public QAbstractListModel
{
	Q_OBJECT

public:
	explicit MessagesModel(QObject *parent = nullptr);
	~MessagesModel();

    Common::Person otherPerson() const;

	//QAbstractItemModel implementation:
	bool hasIndex(int row, int column, const QModelIndex &parent = {}) const;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
	virtual QModelIndex parent(const QModelIndex &child) const override;

	virtual int rowCount(const QModelIndex &parent = {}) const override;
	virtual int columnCount(const QModelIndex &parent = {}) const override;
	virtual bool hasChildren(const QModelIndex &parent = {}) const override;

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

	virtual QHash<int, QByteArray> roleNames() const override;

signals:
	void getMessages(Common::PersonIdType otherId, int count, 
		const std::optional<Common::MessageIdType>& before = {});
	void sendMessages(const std::vector<Common::Message>& messages);
	void error(const QString& error);

	void scrollTo(int row);

public slots:
	//Slots for parent Widget
	void setPerson(const Common::Person& person);
	void startWaiting();
	void stopWaiting();

    void onSendMessage(const QString& text);

	//Slots for requester
	void onSendMessagesResponse(const std::vector<Common::Message>& message);
	void onGetMessagesResponse(Common::PersonIdType otherId, 
		const std::vector<Common::Message>& messages, 
		const std::optional<Common::MessageIdType>& before);

	void onNewMessage(const Common::Person& from, const Common::Message& message);

private:
	void pushFrontMessages(const std::vector<Common::Message>& newMessages, Common::MessageIdType before);
	void pushBackMessages(const std::vector<Common::Message>& newMessages);
	void debugGenerate();

	void saveMessages() const;
	void savePersons() const;

private:
	std::deque<Common::Message> m_messages;
	std::map<Common::PersonIdType, Common::Person> m_person;

	Common::Person m_otherPerson;
	bool m_isWaitForResponse;
	QTimer* m_timer;
};

}
