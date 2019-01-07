#pragma once
#include <QDateTime>
#include <QString>
#include <QUrl>

namespace Models
{

enum class MessageAuthor : quint8
{
	Me,
	Other
};

struct Message
{
public:
	Message(const QDateTime& dateTime,
		const QString& id,
		const QString& name,
		const QString& text,
		const MessageAuthor& author,
		const QUrl& avatar);

public:
	QDateTime dateTime;
	QString id;
	QString name;
	QString text;
	MessageAuthor author;
	QUrl avatar;
};

}