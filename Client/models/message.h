#pragma once
#include <QDateTime>
#include <QString>
#include <QUrl>
#include <QJsonObject>

namespace Models
{

struct Message
{
public:
	Message() = default;

	Message(
		const QDateTime& dateTime,
		const QString& idFrom,
		const QString& idTo,
		const QString& nameFrom,
		const QString& nameTo,
		const QString& text,
		const QUrl& avatar);

	explicit Message(const QJsonObject& json);

	QJsonObject toJson() const;
	

public:
	QDateTime dateTime;

	QString idFrom;
	QString idTo;

	QString nameFrom;
	QString nameTo;

	QString text;
	QUrl avatar;
};

}