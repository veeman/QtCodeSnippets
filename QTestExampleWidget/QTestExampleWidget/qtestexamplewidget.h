#ifndef QTESTEXAMPLEWIDGET_H
#define QTESTEXAMPLEWIDGET_H

#include <QtGui/QWidget>
#include "ui_qtestexamplewidget.h"

class QTestExampleWidget : public QWidget
{
	Q_OBJECT

public:
	QTestExampleWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QTestExampleWidget();

private:
	Ui::QTestExampleWidgetClass ui;
	
};

#endif // QTESTEXAMPLEWIDGET_H
