#pragma once

namespace Ui
{
class Authorization;
};

namespace Widgets
{

class Authorization : public QWidget
{
	Q_OBJECT

public:
	Authorization(QWidget *parent = nullptr);
	~Authorization();

signals:
	void logIn(const QString& login, const QString& password);
	void signUpClicked();
	void error(const QString& error);

private slots:
	void onLogInClicked();

private:
	std::unique_ptr<Ui::Authorization> m_ui;
};

}