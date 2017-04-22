#ifndef QTESTEXAMPLEWIDGET_H
#define QTESTEXAMPLEWIDGET_H

#include <QtWidgets/QWidget>
#include "ui_qtestexamplewidget.h"

class QTestExampleWidget : public QWidget
{
	Q_OBJECT

public:
	QTestExampleWidget(QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
	~QTestExampleWidget();

private:
	Ui::QTestExampleWidgetClass ui;
	
};

#endif // QTESTEXAMPLEWIDGET_H
