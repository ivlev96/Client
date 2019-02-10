#include "authorizationinfo.h"

using namespace Authorization;
using namespace Common;

AuthorizationInfo& Authorization::AuthorizationInfo::instance()
{
	static AuthorizationInfo theSingleInstance;
	return theSingleInstance;
}

Common::PersonIdType AuthorizationInfo::id() const
{
	return m_currentPerson.id;
}

QString AuthorizationInfo::name() const
{
	return m_currentPerson.name();
}

QUrl AuthorizationInfo::avatar() const
{
	return m_currentPerson.avatarUrl;
}

Person AuthorizationInfo::person() const
{
	return m_currentPerson;
}

void AuthorizationInfo::reset(const Person& person)
{
	m_currentPerson = person;
}

AuthorizationInfo::AuthorizationInfo()
	: m_currentPerson(1, "Ivan", "Ivlev", QUrl::fromLocalFile("Vanya.jpg").toString())
{

}
