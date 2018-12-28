#include "widgets/mainwindow/mainwindow.h"
#include <QtWidgets/QApplication>

using namespace Widgets;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
