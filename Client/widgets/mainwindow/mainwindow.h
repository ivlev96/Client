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
struct Person;
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

public slots:
	void onConnected();

private:
	Ui::MainWindow *m_ui;

	Messages* m_messages;
	Contacts* m_contacts;
};

}
