#pragma once
#include "common/person.h"
#include "common/message.h"

namespace Models
{

class PossibleFriendsModel : public QAbstractListModel
{
	Q_OBJECT

public:
	PossibleFriendsModel(QObject *parent);
	~PossibleFriendsModel();

	Common::Person personByRow(int row) const;

	//QAbstractItemModel implementation:
	bool hasIndex(int row, int column, const QModelIndex& parent = {}) const;
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
	virtual QModelIndex parent(const QModelIndex& child) const override;

	virtual int rowCount(const QModelIndex& parent = {}) const override;
	virtual int columnCount(const QModelIndex& parent = {}) const override;
	virtual bool hasChildren(const QModelIndex& parent = {}) const override;

	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	virtual QHash<int, QByteArray> roleNames() const override;

public slots:
	void onFriendsReceived(const std::vector<std::pair<Common::Person, std::optional<Common::Message>>>& persons);

private:
	std::vector<std::pair<Common::Person, std::optional<Common::Message>>> m_persons;
};

}