#pragma once
#include "common/message.h"
#include "common/person.h"
#include <QAbstractListModel>
#include <QTimer>
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
	void getMessages(int otherId, int count);
	void noResponseForMessageRequest();

public slots:
	//Slots for parent Widget
	void setPerson(const Common::Person& person);
	void startWaiting();
	void stopWaiting();

	//Slots for requester
	void onSendMessageResponse(const Common::Message& message, Common::State state);
	void onGetMessagesResponse(int otherId, const std::vector<Common::Message>& messages);

private:
	void pushFrontMessages(const std::vector<Common::Message>& newMessages);
	void pushBackMessages(const std::vector<Common::Message>& newMessages);
	void debugGenerate();

private:
	std::deque<Common::Message> m_messages;

	Common::Person m_otherPerson;
	bool m_isWaitForResponce;
	QTimer* m_timer;
};

}