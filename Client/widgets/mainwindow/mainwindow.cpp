#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/contacts/contacts.h"
#include "widgets/messages/messages.h"
#include "models/messagesmodel.h"

#include <QStackedLayout>

using namespace Widgets;

MainWindow::MainWindow(Models::MessagesModel* messagesModel, QWidget *parent)
	: QMainWindow(parent)
{
	m_ui = new Ui::MainWindow();
	m_ui->setupUi(this);

	m_contacts = new Contacts();
	m_messages = new Messages(messagesModel);
	m_ui->centralWidget->setLayout(new QStackedLayout(this));

	m_ui->centralWidget->layout()->addWidget(m_messages);
	m_ui->centralWidget->layout()->addWidget(m_contacts);

	assert(connect(m_messages, &Messages::sendMessage, this, &MainWindow::sendMessage));
}

MainWindow::~MainWindow()
{
	delete m_ui;
	delete m_contacts;
	delete m_messages;
}

void MainWindow::onConnected()
{
	m_messages->setPerson({ 2, "Pavel", "Zharov", QUrl::fromLocalFile("Pasha.jpg").toString() });
}
