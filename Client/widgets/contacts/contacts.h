#pragma once

namespace Ui 
{ 
	class Contacts; 
};

namespace Widgets
{
	
class Contacts : public QWidget
{
	Q_OBJECT

public:
	Contacts(QWidget *parent = nullptr);
	~Contacts();

private:
	Ui::Contacts *m_ui;
};

}