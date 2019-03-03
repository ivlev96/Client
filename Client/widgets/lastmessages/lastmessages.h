#pragma once
#include "common/person.h"

namespace Ui 
{ 
	class LastMessages; 
};

namespace Models
{
	class LastMessagesModel;
}

namespace Widgets
{
	
class LastMessages : public QWidget
{
	Q_OBJECT

public:
	LastMessages(Models::LastMessagesModel* model, QWidget *parent = nullptr);
	~LastMessages();

signals:
	void personSelected(const Common::Person& person);

private slots:
	void onItemClicked(int index);

private:
	std::unique_ptr<Ui::LastMessages> m_ui;
	std::unique_ptr<QQuickView> m_messagesView;

	Models::LastMessagesModel* m_model;
};

}