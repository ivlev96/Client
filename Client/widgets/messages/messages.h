#pragma once

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
	Messages(Models::MessagesModel* messagesModel, QWidget *parent = nullptr);
	~Messages();

	void setPerson(const Common::Person& other);

private slots:
	void onButtonSendClicked();

private:
	std::unique_ptr<Ui::Messages> m_ui;
    std::unique_ptr<QQuickView> m_messagesView;

	Models::MessagesModel* m_messagesModel;
};

}