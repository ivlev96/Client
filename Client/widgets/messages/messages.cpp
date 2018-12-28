#include "messages.h"
#include "ui_messages.h"

#include "models/messagesmodel.h"

using namespace Widgets;


Messages::Messages(QWidget *parent)
	: QWidget(parent)
{
	m_ui = new Ui::Messages();
	m_ui->setupUi(this);

	m_ui->messages->setModel(new Models::MessagesModel(this));
}

Messages::~Messages()
{
	delete m_ui;
}
