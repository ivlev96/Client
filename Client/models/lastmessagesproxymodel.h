#pragma once

#include <QSortFilterProxyModel>

namespace Models
{

class LastMessagesProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	LastMessagesProxyModel(QObject* parent);
};

}
