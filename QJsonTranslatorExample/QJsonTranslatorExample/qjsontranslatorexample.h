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
#ifndef QJSONTRANSLATOREXAMPLE_H
#define QJSONTRANSLATOREXAMPLE_H

#include <QtGui/QMainWindow>
#include <QAction>
#include "ui_qjsontranslatorexample.h"

class QJsonTranslatorExample : public QMainWindow
{
	Q_OBJECT

public:
	QJsonTranslatorExample(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QJsonTranslatorExample();

protected:
	virtual void changeEvent(QEvent *event);

private:
	Ui::QJsonTranslatorExampleForm ui;
	void getAvailableLanguages();
	bool getInputValues(float &nrone, float &nrtwo);
	void showResult(float value);
	void showInputError();

public slots:
	void on_menuBar_triggered(QAction *action);
	void on_pushButtonAdd_clicked(void);
	void on_pushButtonSubtract_clicked(void);
	void on_pushButtonMultiply_clicked(void);
	void on_pushButtonDivide_clicked(void);
};

#endif // QJSONTRANSLATOREXAMPLE_H
