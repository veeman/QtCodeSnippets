/**
 * QJsonTranslatorExample
 *
 * Copyright 2012 Vitalij Mast <vitalij-mast(at)mage-dev(dot).de>
 *
 * A demonstration how to use JSON syntax for the translations files in a multilingual application.   
 * For more info see http://en.wikipedia.org/wiki/JSON 
 *
 * The json parser used in this project is from https://github.com/ereilin/qt-json
 *
 */
#include "qjsontranslatorexample.h"
#include "qjsontranslator.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create main window
	QJsonTranslatorExample window;
	window.show();
	return app.exec();
}
