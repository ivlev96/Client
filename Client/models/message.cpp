#include "message.h"

Models::Message::Message(
	const QDateTime& dateTime, 
	const QString& id, 
	const QString& name, 
	const QString& text, 
	const MessageAuthor& author, 
	const QImage& avatar)
	: dateTime(dateTime)
	, id(id)
	, name(name)
	, text(text)
	, author(author)
	, avatar(avatar)
{
}
