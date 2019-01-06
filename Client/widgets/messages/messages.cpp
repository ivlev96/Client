#include "messages.h"
#include "ui_messages.h"
#include "models/messagesmodel.h"

#include <QtQml/QQmlContext>

using namespace Widgets;


Messages::Messages(QWidget *parent)
	: QWidget(parent)
{
	m_ui = new Ui::Messages();
	m_ui->setupUi(this);

	m_messagesModel = new Models::MessagesModel(this);


	m_messagesView = new QQuickView();
	QQmlContext* context = m_messagesView->rootContext();
	context->setContextProperty("listModel", m_messagesModel);
	m_messagesView->setSource(QUrl("qrc:/MessageListView.qml"));

	QWidget* container = QWidget::createWindowContainer(m_messagesView, this);

	m_ui->gridLayout->addWidget(container, 0, 0, 1, 2);
}

Messages::~Messages()
{
	delete m_ui;
	delete m_messagesView;
}
