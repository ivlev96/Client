#include "message.h"

using namespace Models;

Message::Message(
	const QDateTime& dateTime,
	const QString& idFrom,
	const QString& idTo,
	const QString& nameFrom,
	const QString& nameTo,
	const QString& text,
	const QUrl& avatar)
	: dateTime(dateTime)
	, idFrom(idFrom)
	, idTo(idTo)
	, nameFrom(nameFrom)
	, nameTo(nameTo)
	, text(text)
	, avatar(avatar)
{
}

Message::Message(const QJsonObject& json)
	: dateTime(QDateTime::fromString(json["dateTime"].toString(), "dd.MM.yyyy hh:mm:ss"))
	, idFrom(json["idFrom"].toString())
	, idTo(json["idTo"].toString())
	, nameFrom(json["nameFrom"].toString())
	, nameTo(json["nameTo"].toString())
	, text(json["text"].toString())
	, avatar(json["avatar"].toString())
{

}

QJsonObject Models::Message::toJson() const
{
	return 
	{
		{ "dateTime", dateTime.toString("dd.MM.yyyy hh:mm:ss") },
		{ "idFrom", idFrom },
		{ "idTo", idTo },
		{ "nameFrom", nameFrom },
		{ "nameTo", nameTo },
		{ "text", text },
		{ "avatar", avatar.toString() }
	};
}
