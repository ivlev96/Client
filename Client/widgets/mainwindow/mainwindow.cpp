#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/contacts/contacts.h"
#include "widgets/messages/messages.h"
#include <QStackedLayout>

using namespace Widgets;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui = new Ui::MainWindow();
	m_ui->setupUi(this);

	m_contacts = new Contacts();
	m_messages = new Messages();
	m_ui->centralWidget->setLayout(new QStackedLayout(this));

	m_ui->centralWidget->layout()->addWidget(m_messages);
	m_ui->centralWidget->layout()->addWidget(m_contacts);
}

MainWindow::~MainWindow()
{
	delete m_ui;
	delete m_contacts;
	delete m_messages;
}