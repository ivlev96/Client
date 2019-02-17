#pragma once

namespace Ui 
{
class Registration;
};

namespace Widgets
{

class Registration : public QWidget
{
	Q_OBJECT

public:
	Registration(QWidget *parent = nullptr);
	~Registration();

signals:
	void logInClicked();
	void error(const QString& error);

	void signUp(
		const QString& firstName,
		const QString& lastName,
		const QString& avatarUrl,
		const QString& login,
		const QString& password);



private slots:
	void onSignUpClicked();

private:
	std::unique_ptr<Ui::Registration> m_ui;
};

}
