#include <QMessageBox>
#include "qjsontranslatorexample.h"
#include "qjsontranslator.h"

#include <QDir>
#include <QDebug>

QJsonTranslatorExample::QJsonTranslatorExample(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	QJsonTranslator::loadLanguage();
	ui.setupUi(this);
	getAvailableLanguages();
}

QJsonTranslatorExample::~QJsonTranslatorExample()
{

}

void QJsonTranslatorExample::changeEvent(QEvent *event)
{
	QWidget::changeEvent(event);

	if(event)
    {
		switch(event->type())
        {
			// this event is send if a translator is loaded
			case QEvent::LanguageChange:
				ui.retranslateUi(this);
			break;

			// this event is send, if the system, language changes
			case QEvent::LocaleChange:
				QJsonTranslator::loadLanguage();	
			break;
			default:
			break;
        }
	}
}

void QJsonTranslatorExample::getAvailableLanguages()
{
	QLocale::Language cur_lang = QJsonTranslator::instance()->locale().language();
	QActionGroup *language_group = new QActionGroup(this);

	// get available language list
	QDir dir(LANGUAGE_STD_PATH);
	QStringList list = dir.entryList(QStringList() << QString("*%1").arg(LANGUAGE_STD_SUFFIX));
	list.prepend("en.json");

	for (int i = 0; i<list.count(); ++i)
	{
		QString name = list[i].left(list[i].length()-QString(LANGUAGE_STD_SUFFIX).length());
		QLocale locale(name);
		QString nativ = locale.nativeLanguageName();

		if (!nativ.isEmpty())
		{
			// create language entry
			QAction *action = new QAction(this);
			action->setText(nativ);
			action->setData(name);
			action->setCheckable(true);
			language_group->addAction(action);
		
			if (cur_lang == locale.language())
				action->setChecked(true);
		}
	}

	// add the list to the menu
	ui.menu_Language->addActions(language_group->actions());
}

bool QJsonTranslatorExample::getInputValues(float &nrone, float &nrtwo)
{
	bool result = false;

	nrone = ui.lineEditNrOne->text().toFloat(&result);
	if (!result)
		return false;

	nrtwo = ui.lineEditNrTwo->text().toFloat(&result);
	if (!result)
		return false;

	return true;
}

void QJsonTranslatorExample::showResult(float value)
{
	QString text = QString(tr("The result value is: %1")).arg(value);
	QMessageBox::information(this, tr("Result"), text);
}


void QJsonTranslatorExample::showInputError()
{
	QMessageBox::critical(this, tr("Error"), tr("Invalid Input"));
}

void QJsonTranslatorExample::on_menuBar_triggered(QAction *action)
{
	if (action == ui.action_Exit)
		close();
	else
	{
		// change language
		if (action->data().type() == QVariant::String)
		{
			QLocale newlanguage(action->data().toString());
			QJsonTranslator::loadLanguage(&newlanguage);
		}
	}
}

void QJsonTranslatorExample::on_pushButtonAdd_clicked(void)
{
	float one, two;
	if (getInputValues(one, two))
		showResult(one+two);
	else
		showInputError();
}

void QJsonTranslatorExample::on_pushButtonSubtract_clicked(void)
{
	float one, two;
	if (getInputValues(one, two))
		showResult(one-two);
	else
		showInputError();
}

void QJsonTranslatorExample::on_pushButtonMultiply_clicked(void)
{
	float one, two;
	if (getInputValues(one, two))
		showResult(one*two);
	else
		showInputError();
}

void QJsonTranslatorExample::on_pushButtonDivide_clicked(void)
{
	float one, two;
	if (getInputValues(one, two))
		showResult(one/two);
	else
		showInputError();
}

