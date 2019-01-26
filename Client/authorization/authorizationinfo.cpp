#include "authorizationinfo.h"

using namespace Authorization;
using namespace Common;

int AuthorizationInfo::id() const
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

void AuthorizationInfo::reset(const Person& person)
{
	m_currentPerson = person;
}

AuthorizationInfo::AuthorizationInfo()
	: m_currentPerson(1, "Ivan", "Ivlev", QUrl::fromLocalFile("Vanya.jpg").toString())
{

}
