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

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Models::LastMessagesModel* lastMessagesModel, 
		Models::MessagesModel* messagesModel, 
		QWidget *parent = nullptr);

	~MainWindow();

	void showError(const QString& error) const;

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
	std::unique_ptr<Ui::MainWindow> m_ui;

	std::unique_ptr<QStackedLayout> m_layout;

	std::unique_ptr<Authorization> m_authorization;
	std::unique_ptr<Registration> m_registration;
	std::unique_ptr<LastMessages> m_lastMessages;
	std::unique_ptr<Messages> m_messages;
};

}
