#include "mainwindow.h"
#include "authorization/authorizationinfo.h"
#include "models/messagesmodel.h"
#include "models/lastmessagesmodel.h"

using namespace Widgets;

MainWindow::MainWindow(Models::LastMessagesModel* lastMessagesModel,
	Models::MessagesModel* messagesModel)
	: m_engine()
{
	qmlRegisterUncreatableMetaObject(
		Widgets::staticMetaObject,	// static meta object
		"cppnamespace",				// import statement (can be any string)
		1, 0,                       // major and minor version of the import
		"Widgets",					// name in QML (does not have to match C++ name)
		"Error: only enums"			// error in case someone tries to create a MyNamespace object
	);

	Q_UNUSED(lastMessagesModel);
	Q_UNUSED(messagesModel);

	auto rootContext = m_engine.rootContext();
	ASSERT_NOT_NULL(rootContext);

	rootContext->setContextProperty("CppParent", this);
	rootContext->setContextProperty("lastMessagesModel", lastMessagesModel);
	rootContext->setContextProperty("messagesModel", messagesModel);

	m_engine.load(QUrl("qrc:/MainWindowDesktop.qml"));

	auto authorizationWidget = m_engine.rootObjects()[0]->findChild<QObject*>("authorization");
	ASSERT_NOT_NULL(authorizationWidget);

	auto lastMessagesWidget = m_engine.rootObjects()[0]->findChild<QObject*>("lastMessagesListView");
    ASSERT_NOT_NULL(lastMessagesWidget);

    auto messagesWidget = m_engine.rootObjects()[0]->findChild<QObject*>("messages");
    ASSERT_NOT_NULL(messagesWidget);

	VERIFY(connect(authorizationWidget, SIGNAL(logIn(QString, QString)), SIGNAL(logIn(const QString&, const QString&))));
	VERIFY(connect(lastMessagesWidget, SIGNAL(itemClicked(int)), SIGNAL(personSelected(int))));
    VERIFY(connect(messagesWidget, SIGNAL(sendMessage(QString)), SIGNAL(sendMessage(const QString&))));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showError(const QString& error)
{
	Q_UNUSED(error);
}

void MainWindow::onConnected()
{

}

void MainWindow::onLogInResponse(const std::optional<Common::Person>& person)
{
	if (person)
	{
		::Authorization::AuthorizationInfo::instance().reset(*person);
		emit switchToContent();
	}
	else
	{
		emit error("Wrong login or password");
	}
}

void MainWindow::onSignUpResponse(const std::optional<Common::Person>& person)
{
	if (person)
	{
		::Authorization::AuthorizationInfo::instance().reset(*person);
		emit switchToContent();
	}
	else
	{
		emit error("Login is already in use");
	}
}

void MainWindow::onPersonSelected(const Common::Person& person)
{
	Q_UNUSED(person);
	//m_messages->setPerson(person);
	//switchToMessages();
}
