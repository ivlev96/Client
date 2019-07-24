#include "mainwindow.h"
#include "authorization/authorizationinfo.h"

using namespace Widgets;

MainWindow::MainWindow(
	QAbstractItemModel* lastMessagesModel,
	QAbstractItemModel* messagesModel,
	QAbstractItemModel* possibleFriendsModel)
	: m_engine()
{
	qmlRegisterUncreatableMetaObject(
		Widgets::staticMetaObject,	// static meta object
		"cppnamespace",				// import statement (can be any string)
		1, 0,                       // major and minor version of the import
		"Widgets",					// name in QML (does not have to match C++ name)
		"Error: only enums"			// error in case someone tries to create a MyNamespace object
	);

	auto rootContext = m_engine.rootContext();
	ASSERT_NOT_NULL(rootContext);

	rootContext->setContextProperty("CppParent", this);
	rootContext->setContextProperty("lastMessagesModel", lastMessagesModel);
	rootContext->setContextProperty("messagesModel", messagesModel);
	rootContext->setContextProperty("possibleFriendsModel", possibleFriendsModel);

#if defined(Q_OS_ANDROID)
	m_engine.load(QUrl("qrc:/MainWindowMobile.qml"));
#else
	m_engine.load(QUrl("qrc:/MainWindowDesktop.qml"));
#endif

	auto rootObjects = m_engine.rootObjects();
	ASSERT(!rootObjects.isEmpty());

	auto authorizationWidget = rootObjects[0]->findChild<QObject*>("authorization");
	ASSERT_NOT_NULL(authorizationWidget);

	auto lastMessagesWidget = rootObjects[0]->findChild<QObject*>("lastMessagesListView");
    ASSERT_NOT_NULL(lastMessagesWidget);

    auto messagesWidget = rootObjects[0]->findChild<QObject*>("messages");
    ASSERT_NOT_NULL(messagesWidget);

	auto possibleFriends = rootObjects[0]->findChild<QObject*>("possibleFriends");
	ASSERT_NOT_NULL(possibleFriends);

	auto possibleFriendsListView = rootObjects[0]->findChild<QObject*>("possibleFriendsListView");
	ASSERT_NOT_NULL(possibleFriendsListView);

	auto filterFriends = rootObjects[0]->findChild<QObject*>("filterFriends");
	ASSERT_NOT_NULL(filterFriends);

	VERIFY(connect(authorizationWidget, SIGNAL(logIn(QString, QString)), SIGNAL(logIn(const QString&, const QString&))));
	VERIFY(connect(lastMessagesWidget, SIGNAL(itemClicked(int)), SIGNAL(personSelected(int))));
    VERIFY(connect(messagesWidget, SIGNAL(sendMessage(QString)), SIGNAL(sendMessage(const QString&))));
    VERIFY(connect(possibleFriends, SIGNAL(findFriends(QString, bool, bool)), SIGNAL(findFriends(const QString&, bool, bool))));
	VERIFY(connect(possibleFriendsListView, SIGNAL(itemClicked(int)), SIGNAL(possibleFriendSelected(int))));
    VERIFY(connect(filterFriends, SIGNAL(filterFriendsTextChanged(QString)), SIGNAL(filterFriendsTextChanged(const QString&))));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showError(const QString& error)
{
	qDebug() << error;
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
