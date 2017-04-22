#ifndef QJSONTRANSLATOREXAMPLE_H
#define QJSONTRANSLATOREXAMPLE_H

#include <QtWidgets/QMainWindow>
#include <QAction>
#include "ui_qjsontranslatorexample.h"

class QJsonTranslatorExample : public QMainWindow
{
	Q_OBJECT

public:
	QJsonTranslatorExample(QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
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
