#pragma once

namespace Ui
{
class MainWindow;
}

namespace Models
{
class MessagesModel;
class LastMessagesModel;
}

namespace Common
{
struct Person;
}

namespace Widgets
{

class Messages;
class LastMessages;
class Authorization;
class Registration;

class MainWindow : public QObject
{
	Q_OBJECT

public:
	MainWindow(Models::LastMessagesModel* lastMessagesModel, 
		Models::MessagesModel* messagesModel);

	~MainWindow();

	void showError(const QString& error);

signals:
	void error(const QString& message);
	void logIn(const QString& login, const QString& password);

	void signUp(
		const QString& firstName,
		const QString& lastName,
		const QString& avatarUrl,
		const QString& login,
		const QString& password);

public slots:
	void onConnected();
	void onLogInResponse(bool ok, const std::optional<Common::Person>& person);
	void onSignUpResponse(bool ok, const std::optional<Common::Person>& person);

private slots:
	void onPersonSelected(const Common::Person& person);

	void switchToRegistration();
	void switchToAuthorization();
	void switchToLastMessages();
	void switchToMessages();

private:
	QQmlApplicationEngine m_engine;

};

}
