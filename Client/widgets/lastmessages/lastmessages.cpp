#include "lastmessages.h"
#include "ui_lastmessages.h"

#include "models/lastmessagesmodel.h"

using namespace Widgets;

LastMessages::LastMessages(Models::LastMessagesModel* model, QWidget *parent)
	: QWidget(parent)
	, m_model(model)
	, m_ui(std::make_unique<Ui::LastMessages>())
	, m_messagesView(std::make_unique<QQuickView>())
{
	m_ui->setupUi(this);

	QQmlContext* context = m_messagesView->rootContext();
	context->setContextProperty("listModel", m_model);
	m_messagesView->setSource(QUrl("qrc:/LastMessagesListView.qml"));
    QObject* lastMessagesView = m_messagesView->rootObject();
    VERIFY(connect(lastMessagesView, SIGNAL(itemClicked(int)), this, SLOT(onItemClicked(int))));

	QWidget* container = QWidget::createWindowContainer(m_messagesView.get(), this);
	m_ui->gridLayout->addWidget(container);
}

LastMessages::~LastMessages()
{
}

void LastMessages::onItemClicked(int index)
{
	emit personSelected(m_model->personByRow(index));
}
