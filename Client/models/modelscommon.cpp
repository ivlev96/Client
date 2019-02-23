#include "modelscommon.h"

QHash<int, QByteArray> Models::roleNames()
{
	static const QHash<int, QByteArray> roles
	{
		{ Qt::DisplayRole, "messageText" },
		{ MessagesDataRole::MessageAuthorRole, "messageAuthor" },
		{ MessagesDataRole::MessageShortAuthorRole, "messageShortAuthor" },
		{ MessagesDataRole::MessageTimeRole, "messageTime" },
		{ MessagesDataRole::MessageAvatarRole, "messageAvatar" },
		{ MessagesDataRole::MessageIsFromMeRole, "messageIsFromMe" },
		{ MessagesDataRole::MessageStateRole, "messageState" }
	};

	return roles;
}