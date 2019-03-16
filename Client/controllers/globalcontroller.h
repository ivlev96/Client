#pragma once

#include "widgets/mainwindow/mainwindow.h"
#include "models/messagesmodel.h"
#include "models/lastmessagesmodel.h"
#include "network/requester.h"

namespace Controllers
{

class GlobalController : public QObject
{
	Q_OBJECT

public:
	GlobalController();
	~GlobalController();

public slots:
	void onError(const QString& error);
	void onPersonSelected(int row);

private:
	std::unique_ptr<Widgets::MainWindow> m_mainWindow;

	Models::MessagesModel* m_messagesModel;
	Models::LastMessagesModel* m_lastMessagesModel;

	Network::Requester* m_requester;

	QThread* m_requesterThread;
};

}