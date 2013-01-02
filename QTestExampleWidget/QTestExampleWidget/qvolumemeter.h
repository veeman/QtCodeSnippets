#ifndef QVOLUMEMETER_H
#define QVOLUMEMETER_H

#include <QWidget>
#include <QImage>

class QVolumeMeter : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(float levelMin READ levelMin WRITE setLevelMin)
	Q_PROPERTY(float levelMax READ levelMax WRITE setLevelMax)
	Q_PROPERTY(float level READ level WRITE setLevel)
public:
	QVolumeMeter(QWidget *parent);
	~QVolumeMeter();

	float levelMin() const;
	float levelMax() const;
	float level() const;

public slots:
	void setLevelMin(float min);
	void setLevelMax(float max);
	void setLevel(float lvl);
	void setPercent(int value);

protected:
	virtual void paintEvent(QPaintEvent *event);

private:
	QImage *pTemplate;
	float   pLevel;
	float   pLevelMin;
	float   pLevelMax;
};

inline float QVolumeMeter::levelMin() const
{ return this->pLevelMin; };

inline float QVolumeMeter::levelMax() const
{ return this->pLevelMax; };

inline float QVolumeMeter::level() const
{ return this->pLevel; };

inline void QVolumeMeter::setPercent(int value) {
  setLevel(this->pLevelMin + (this->pLevelMax - this->pLevelMin) * (float(value) / 100.f));	
}


#endif // QVOLUMEMETER_H
