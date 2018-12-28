#pragma once

#include <QWidget>
namespace Ui 
{ 
	class Messages; 
};

namespace Widgets
{

class Messages : public QWidget
{
	Q_OBJECT

public:
	Messages(QWidget *parent = nullptr);
	~Messages();

private:
	Ui::Messages *m_ui;
};

}