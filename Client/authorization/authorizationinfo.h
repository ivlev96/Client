#pragma once
#include "common/person.h"

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

	Common::PersonIdType id() const;
	QString name() const;
	QUrl avatar() const;

	Common::Person person() const;

	void reset(const Common::Person& person);

private:
	AuthorizationInfo();
	AuthorizationInfo(const AuthorizationInfo& root) = delete;
	AuthorizationInfo& operator=(const AuthorizationInfo&) = delete;

private:
	Common::Person m_currentPerson;
};

}