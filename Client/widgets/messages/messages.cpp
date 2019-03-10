#include "messages.h"
#include "ui_messages.h"
#include "models/messagesmodel.h"

using namespace Widgets;
using namespace Common;

Messages::Messages(Models::MessagesModel* messagesModel, QWidget *parent)
	: QWidget(parent)
	, m_messagesModel(messagesModel)
	, m_ui(std::make_unique<Ui::Messages>())
    , m_messagesView(std::make_unique<QQuickView>())
{
    m_ui->setupUi(this);

    QQmlContext* context = m_messagesView->rootContext();
	context->setContextProperty("listModel", m_messagesModel);
	m_messagesView->setSource(QUrl("qrc:/MessagesListView.qml"));

	QWidget* container = QWidget::createWindowContainer(m_messagesView.get(), this);

    m_ui->verticalLayout->insertWidget(0, container);

	VERIFY(connect(m_ui->buttonSend, &QPushButton::clicked, this, &Messages::onButtonSendClicked));
}

Messages::~Messages()
{
}

void Messages::setPerson(const Person& other)
{
	m_messagesModel->setPerson(other);
}

void Messages::onButtonSendClicked()
{
	m_messagesModel->addNewMessage(m_ui->newMessage->toPlainText());
	m_ui->newMessage->clear();
}
