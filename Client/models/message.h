#pragma once
#include <QDateTime>
#include <QString>
#include <QImage>


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
		const QImage& avatar = {});

public:
	QDateTime dateTime;
	QString id;
	QString name;
	QString text;
	MessageAuthor author;
	QImage avatar;
};

}