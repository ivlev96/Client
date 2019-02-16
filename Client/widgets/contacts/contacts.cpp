#include "contacts.h"
#include "ui_contacts.h"

using namespace Widgets;

Contacts::Contacts(QWidget *parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::Contacts>())
{
	m_ui->setupUi(this);
}

Contacts::~Contacts()
{
}
