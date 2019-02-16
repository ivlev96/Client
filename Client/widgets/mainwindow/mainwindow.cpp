#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorization/authorizationinfo.h"
#include "widgets/authorization/authorization.h"
#include "widgets/contacts/contacts.h"
#include "widgets/messages/messages.h"
#include "models/messagesmodel.h"

using namespace Widgets;

MainWindow::MainWindow(Models::MessagesModel* messagesModel, QWidget *parent)
	: QMainWindow(parent)
{
	m_ui = std::make_unique<Ui::MainWindow>();
	m_ui->setupUi(this);

	m_authorization = std::make_unique<Authorization>();
	m_contacts = std::make_unique<Contacts>();
	m_messages = std::make_unique<Messages>(messagesModel);

	m_layout = std::make_unique<QStackedLayout>();
	m_ui->centralWidget->setLayout(m_layout.get());

	m_layout->addWidget(m_authorization.get());
	m_layout->addWidget(m_contacts.get());
	m_layout->addWidget(m_messages.get());

	m_layout->setCurrentWidget(m_authorization.get());

	assert(connect(m_authorization.get(), &Authorization::error, this, &MainWindow::error));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showError(const QString& error) const
{
	m_ui->statusBar->showMessage(error, 2000);
}

void MainWindow::onLogInResponse(bool ok, const std::optional<Common::Person>& person)
{
	if (ok)
	{
		::Authorization::AuthorizationInfo::instance().reset(*person);
		m_layout->setCurrentWidget(m_contacts.get());
	}
	else
	{
		emit error("Wrong login or password");
	}
}

void MainWindow::onConnected()
{
	m_messages->setPerson({ 2, "Pavel", "Zharov", QUrl::fromLocalFile("Pasha.jpg").toString() });
}
