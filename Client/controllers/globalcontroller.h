#pragma once

#include "widgets/mainwindow/mainwindow.h"
#include "models/messagesmodel.h"
#include "network/requester.h"

#include <QObject>
#include <QThread>

namespace Controllers
{

class GlobalController : public QObject
{
	Q_OBJECT

public:
	GlobalController();
	~GlobalController();

	void run();

public slots:
	void onError(const QString& error);

private:
	Widgets::MainWindow* m_mainWindow;

	Models::MessagesModel* m_messagesModel;

	Network::Requester* m_requester;

	QThread* m_requesterThread;
};

}