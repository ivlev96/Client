#pragma once

#include <QtWidgets/QMainWindow>

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
class Person;
}

namespace Widgets
{

class Messages;
class Contacts;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Models::MessagesModel* messagesModel, QWidget *parent = nullptr);
	~MainWindow();

signals:
	void sendMessage(const Common::Person& other, const QString& message);

private:
	Ui::MainWindow *m_ui;

	Messages* m_messages;
	Contacts* m_contacts;
};

}
