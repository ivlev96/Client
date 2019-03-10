#include "authorization.h"
#include "ui_authorization.h"

using namespace Widgets;

Authorization::Authorization(QWidget *parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::Authorization>())
{
	m_ui->setupUi(this);

#ifdef Q_OS_ANDROID
    m_ui->login->setMinimumWidth(this->width()/2);
    m_ui->login->setMaximumWidth(this->width()/2);

    m_ui->password->setMinimumWidth(this->width()/2);
    m_ui->password->setMaximumWidth(this->width()/2);

    m_ui->buttonLogIn->setMinimumWidth(this->width()/2);
    m_ui->buttonLogIn->setMaximumWidth(this->width()/2);

    QFont font;
    font.setPointSize(16);
    m_ui->label->setFont(font);
    m_ui->login->setFont(font);
    m_ui->password->setFont(font);
    m_ui->buttonLogIn->setFont(font);
#endif

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
