#pragma once

namespace Ui
{
class MainWindow;
}

namespace Models
{
class MessagesModel;
}

namespace Common
{
struct Person;
}

namespace Widgets
{

class Messages;
class Contacts;
class Authorization;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Models::MessagesModel* messagesModel, QWidget *parent = nullptr);
	~MainWindow();

	void showError(const QString& error) const;

signals:
	void error(const QString& message);
	void logIn(const QString& login, const QString& password);

public slots:
	void onConnected();
	void onLogInResponse(bool ok, const std::optional<Common::Person>& person);

private:
	std::unique_ptr<Ui::MainWindow> m_ui;

	std::unique_ptr<QStackedLayout> m_layout;

	std::unique_ptr<Authorization> m_authorization;
	std::unique_ptr<Contacts> m_contacts;
	std::unique_ptr<Messages> m_messages;
};

}
