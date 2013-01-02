#include "qtestexamplewidget.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTestExampleWidget w;
	w.show();
	return a.exec();
}
