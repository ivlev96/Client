#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui
{
	class MainWindow;
}

namespace Widgets
{
	class Messages;
	class Contacts;

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private:
		Ui::MainWindow *m_ui;

		Messages* m_messages;
		Contacts* m_contacts;
	};
}
