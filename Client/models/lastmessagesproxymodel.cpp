#include "lastmessagesproxymodel.h"
#include "modelscommon.h"

using namespace Models;

LastMessagesProxyModel::LastMessagesProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent)
{
	setSortRole(MessagesDataRole::MessageTimeRole);
	setSortCaseSensitivity(Qt::CaseInsensitive);

	setFilterCaseSensitivity(Qt::CaseInsensitive);
	setFilterRole(MessagesDataRole::MessageAuthorRole);
}
