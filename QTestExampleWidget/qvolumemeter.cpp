#include "qvolumemeter.h"
#include <QPainter>

QVolumeMeter::QVolumeMeter(QWidget *parent)
	: QWidget(parent), pTemplate(0), pLevel(0.5f), pLevelMin(0.f), pLevelMax(1.f)
{
	this->pTemplate = new QImage(":/QTestExampleWidget/Resources/volumeMeter.png");
	if (pTemplate)
	{
		QSize nsize(pTemplate->width()/2, pTemplate->height());
		setMinimumSize(nsize);
		setMaximumSize(nsize);
	}
}

QVolumeMeter::~QVolumeMeter()
{
	delete this->pTemplate;
}

void QVolumeMeter::setLevelMin(float min)
{ 
	this->pLevelMin=min; 
	if (this->pLevelMax<this->pLevelMin)
		qSwap(this->pLevelMax, this->pLevelMin);
	this->update(); 
};

void QVolumeMeter::setLevelMax(float max)
{ 
	this->pLevelMax=max; 
	if (this->pLevelMax<this->pLevelMin)
		qSwap(this->pLevelMax, this->pLevelMin);
	this->update(); 
};

void QVolumeMeter::setLevel(float lvl)
{ 
	this->pLevel=lvl; 
	if (this->pLevel>this->pLevelMax)
		this->pLevel=this->pLevelMax;
	else
	if (this->pLevel<this->pLevelMin)
		this->pLevel=this->pLevelMin;
	this->update(); 
};


void QVolumeMeter::paintEvent(QPaintEvent *event)
{
	if (!pTemplate)
		return;

	QPainter painter(this);
	painter.drawImage(0, 0, *pTemplate, width(), 0);

	float range = (this->pLevelMax - this->pLevelMin);
	float pos = (range-(this->pLevel - this->pLevelMin)/range)* float(this->height()) ;
	QRect rect(0, pos, this->width(), this->height());
	painter.drawImage(rect, *pTemplate, rect);

	painter.end();
}
