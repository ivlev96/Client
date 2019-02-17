#include "registration.h"
#include "ui_registration.h"

using namespace Widgets;

Registration::Registration(QWidget *parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::Registration>())
{
	m_ui->setupUi(this);

	assert(connect(m_ui->logIn, &QPushButton::clicked, this, &Registration::logInClicked));
	assert(connect(m_ui->signUp, &QPushButton::clicked, this, &Registration::onSignUpClicked));
}

Registration::~Registration()
{
}

void Registration::onSignUpClicked()
{
	const QString firstName = m_ui->firstName->text();
	const QString lastName = m_ui->lastName->text();
	const QString avatarUrl;
	const QString login = m_ui->login->text();
	const QString password = m_ui->password->text();
	const QString repeatPassword = m_ui->repeatPassword->text();

	if (firstName.isEmpty())
	{
		emit error("First name is empty");
	}
	else if (lastName.isEmpty())
	{
		emit error("Last name is empty");
	}
	else if (login.isEmpty())
	{
		emit error("Login is empty");
	}
	else if (password.isEmpty())
	{
		emit error("Password name is empty");
	}
	else if (password != repeatPassword)
	{
		emit error("Repeat password correctly");
	}
	else
	{
		emit signUp(
			firstName,
			lastName,
			avatarUrl,
			login,
			password
		);
	}
}
