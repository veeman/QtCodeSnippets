#include "qjsontranslatorexample.h"
#include "qjsontranslator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create main window
	QJsonTranslatorExample window;
	window.show();
	return app.exec();
}
