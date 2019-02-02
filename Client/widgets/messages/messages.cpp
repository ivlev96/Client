#include "messages.h"
#include "ui_messages.h"
#include "models/messagesmodel.h"

#include <QtQml/QQmlContext>

using namespace Widgets;
using namespace Common;

Messages::Messages(Models::MessagesModel* messagesModel, QWidget *parent)
	: QWidget(parent)
	, m_messagesModel(messagesModel)
{
	m_ui = new Ui::Messages();
	m_ui->setupUi(this);

	m_messagesView = new QQuickView();
	QQmlContext* context = m_messagesView->rootContext();
	context->setContextProperty("listModel", m_messagesModel);
	m_messagesView->setSource(QUrl("qrc:/MessageListView.qml"));

	QWidget* container = QWidget::createWindowContainer(m_messagesView, this);

	m_ui->gridLayout->addWidget(container, 0, 0, 1, 2);

	assert(connect(m_ui->buttonSend, &QPushButton::clicked, this, &Messages::onButtonSendClicked));
}

Messages::~Messages()
{
	delete m_ui;
	delete m_messagesView;
}

void Messages::setPerson(const Person& other)
{
	m_messagesModel->setPerson(other);
}

void Messages::onButtonSendClicked()
{
	emit sendMessage(m_messagesModel->otherPerson(), m_ui->newMessage->toPlainText());
}
