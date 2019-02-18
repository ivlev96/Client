#pragma once

namespace Models
{

enum MessagesDataRole
{
	MessageAuthorRole = Qt::UserRole + 1,
	MessageTimeRole,
	MessageAvatarRole,
	MessageIsFromMeRole,
	MessageStateRole
};

}