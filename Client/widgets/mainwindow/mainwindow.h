#pragma once

namespace Ui
{
class MainWindow;
}

namespace Common
{
struct Person;
}

namespace Widgets
{

Q_NAMESPACE
enum WidgetNumber
{
	Authorization = 0,
	Registration,
	Content
};
Q_ENUM_NS(WidgetNumber)

class Messages;
class LastMessages;
class Authorization;
class Registration;

class MainWindow : public QObject
{
	Q_OBJECT

public:
	MainWindow(QAbstractItemModel* lastMessagesModel,
		QAbstractItemModel* messagesModel,
		QAbstractItemModel* possibleFriendsModel);

	~MainWindow();

	void showError(const QString& error);

signals:
	void error(const QString& message);
	void logIn(const QString& login, const QString& password);
	void personSelected(int row);
	void possibleFriendSelected(int row);

    void sendMessage(const QString& message);

	void signUp(
		const QString& firstName,
		const QString& lastName,
		const QString& avatarUrl,
		const QString& login,
		const QString& password);

	void findFriends(const QString& name, bool withMessages, bool withoutMessages);
	void filterFriendsTextChanged(const QString& text);
	void switchToContent();

public slots:
	void onConnected();
	void onLogInResponse(const std::optional<Common::Person>& person);
	void onSignUpResponse(const std::optional<Common::Person>& person);

private:
	QQmlApplicationEngine m_engine;
};

}
