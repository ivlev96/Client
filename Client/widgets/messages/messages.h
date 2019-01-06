#pragma once

#include <QWidget>
#include <QtQuick/QQuickView>

namespace Ui 
{ 
	class Messages; 
};

namespace Models
{
	class MessagesModel;
}

namespace Widgets
{

class Messages : public QWidget
{
	Q_OBJECT

public:
	Messages(QWidget *parent = nullptr);
	~Messages();

private:
	Ui::Messages* m_ui;
	Models::MessagesModel* m_messagesModel;
	QQuickView* m_messagesView;
};

}