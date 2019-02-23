#pragma once

namespace Models
{

enum MessagesDataRole
{
	MessageAuthorRole = Qt::UserRole + 1,
	MessageShortAuthorRole,
	MessageTimeRole,
	MessageAvatarRole,
	MessageIsFromMeRole,
	MessageStateRole
};

QHash<int, QByteArray> roleNames();

}