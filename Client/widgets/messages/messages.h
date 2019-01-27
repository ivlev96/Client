#pragma once

#include <QWidget>
#include <QtQuick/QQuickView>
#include "common/person.h"

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

	void setPerson(const Common::Person& person);

private:
	Ui::Messages* m_ui;
	Models::MessagesModel* m_messagesModel;
	QQuickView* m_messagesView;

	Common::Person m_otherPerson;
};

}