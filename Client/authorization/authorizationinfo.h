#pragma once
#include <QString>
#include <QUrl>

namespace Authorization
{

class AuthorizationInfo
{
public:
	static AuthorizationInfo& instance()
	{
		static AuthorizationInfo theSingleInstance;
		return theSingleInstance;
	}

	QString id() const;
	QString name() const;
	QUrl avatar() const;

	void reset(const QString& id, const QString& name, const QUrl& avatar);

private:
	AuthorizationInfo();
	AuthorizationInfo(const AuthorizationInfo& root) = delete;
	AuthorizationInfo& operator=(const AuthorizationInfo&) = delete;

private:
	QString m_currentId;
	QString m_currentName;
	QUrl m_currentAvatar;
};

}