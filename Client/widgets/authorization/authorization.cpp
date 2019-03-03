#include "authorization.h"
#include "ui_authorization.h"

using namespace Widgets;

Authorization::Authorization(QWidget *parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::Authorization>())
{
	m_ui->setupUi(this);

	VERIFY(connect(m_ui->buttonLogIn, &QPushButton::clicked, this, &Authorization::onLogInClicked));
	VERIFY(connect(m_ui->signUp, &QPushButton::clicked, this, &Authorization::signUpClicked));
}

Authorization::~Authorization()
{

}

void Authorization::onLogInClicked()
{
	const QString login = m_ui->login->text();
	const QString password = m_ui->password->text();

	if (login.isEmpty() && password.isEmpty())
	{
		emit error("Login and password are empty");
	}
	else if (login.isEmpty())
	{
		emit error("Login is empty");
	}
	else if (password.isEmpty())
	{
		emit error("Password is empty");
	}
	else
	{
		emit logIn(login, password);

		m_ui->login->clear();
		m_ui->password->clear();
	}
}