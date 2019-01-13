#include "authorizationinfo.h"

using namespace Authorization;

QString AuthorizationInfo::id() const
{
	return m_currentId;
}

QString AuthorizationInfo::name() const
{
	return m_currentName;
}

QUrl AuthorizationInfo::avatar() const
{
	return m_currentAvatar;
}

void AuthorizationInfo::reset(const QString& id, const QString& name, const QUrl& avatar)
{
	m_currentId = id;
	m_currentName = name;
	m_currentAvatar = avatar;
}

AuthorizationInfo::AuthorizationInfo()
	: m_currentId("1")
	, m_currentName("Ivan Ivlev")
	, m_currentAvatar(QUrl::fromLocalFile("Vanya.jpg"))
{

}
