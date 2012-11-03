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
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include "json.h"
#include "qjsontranslator.h"

#include <QDebug>

const char *LANGUAGE_STD_PATH	= "./lang/";
const char *LANGUAGE_STD_SUFFIX = ".json";

static QString find_translation(const QLocale & locale,
                                const QString & filename,
                                const QString & prefix,
                                const QString & directory,
                                const QString & suffix)
{
    QString path;
    if (QFileInfo(filename).isRelative()) {
        path = directory;
        if (!path.isEmpty() && !path.endsWith(QLatin1Char('/')))
            path += QLatin1Char('/');
    }

    QFileInfo fi;
    QString realname;
    QStringList fuzzyLocales;

    // see http://www.unicode.org/reports/tr35/#LanguageMatching for inspiration
    QStringList languages = locale.uiLanguages();

#if defined(Q_OS_UNIX) && !defined(Q_OS_SYMBIAN)
    for (int i = languages.size()-1; i >= 0; --i) {
        QString lang = languages.at(i);
        QString lowerLang = lang.toLower();
        if (lang != lowerLang)
            languages.insert(i+1, lowerLang);
    }
#endif

    // try explicit locales names first
    foreach (QString localeName, languages) {
        localeName.replace(QLatin1Char('-'), QLatin1Char('_'));
        realname = path + filename + prefix + localeName + (suffix.isNull() ? QLatin1String(LANGUAGE_STD_SUFFIX) : suffix);
        fi.setFile(realname);
        if (fi.isReadable() && fi.isFile())
            return realname;

        realname = path + filename + prefix + localeName;
        fi.setFile(realname);

        if (fi.isReadable() && fi.isFile())
            return realname;

        fuzzyLocales.append(localeName);
    }


    // start guessing
    foreach (QString localeName, fuzzyLocales) {
        for (;;) {
            int rightmost = localeName.lastIndexOf(QLatin1Char('_'));
            // no truncations? fail
            if (rightmost <= 0)
                break;
            localeName.truncate(rightmost);

            realname = path + filename + prefix + localeName + (suffix.isNull() ? QLatin1String(LANGUAGE_STD_SUFFIX) : suffix);
            fi.setFile(realname);
            if (fi.isReadable() && fi.isFile())
                return realname;

            realname = path + filename + prefix + localeName;
            fi.setFile(realname);
            if (fi.isReadable() && fi.isFile())
                return realname;
        }
    }

    if (!suffix.isNull()) {
        realname = path + filename + suffix;
        fi.setFile(realname);
        if (fi.isReadable() && fi.isFile())
            return realname;
    }

    realname = path + filename + prefix;
    fi.setFile(realname);
    if (fi.isReadable() && fi.isFile())
        return realname;

    realname = path + filename;
    fi.setFile(realname);

    if (fi.isReadable() && fi.isFile())
        return realname;

    return QString();
}


QJsonTranslator* QJsonTranslator::instance(void)
{
	static QJsonTranslator* translator = NULL;
	if (!translator)
		translator = new QJsonTranslator(qApp);

	return translator;
}

int QJsonTranslator::loadLanguage(const QLocale *lang)
{
	QJsonTranslator* translator = QJsonTranslator::instance();

	if (qApp)
	{
		QLocale tLang = lang ? *lang : QLocale::system();

		qApp->removeTranslator(translator);
		translator->load(tLang, "", "", LANGUAGE_STD_PATH);
		qApp->installTranslator(translator);
		return 0;
	}

	return -1;
}


QJsonTranslator::QJsonTranslator(QObject *parent, QLocale &default)
	: QTranslator(parent), pLoaded(false), pDefaultLocale(default), pCurrentLocale(default)
{

}

QJsonTranslator::~QJsonTranslator()
{
	if (qApp)
		qApp->removeTranslator(this);
}

bool QJsonTranslator::load(const QLocale &locale,  const QString &filename,
		  const QString &prefix,   const QString &directory,
		  const QString &suffix)
{
	pLanguageStrip.clear();
	if (pDefaultLocale == locale)
		return  this->pLoaded = true;

	QString realName = find_translation(locale, filename, prefix, directory, suffix);
	if (this->do_load(realName))
	{
		this->pCurrentLocale = locale;
		return this->pLoaded = true;
	}

	return this->pLoaded = false;
}

bool QJsonTranslator::do_load(const QString &realname)
{
	QFile tFile(realname);

	if (tFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream tStream(&tFile);
		QString tData = tStream.readAll();
		tFile.close();
		bool ok;

		QVariant tMap = QtJson::Json::parse(tData, ok);
		if (ok)
		{
			pLanguageStrip = tMap;
		}
		else
			return false;
	}
	else
		return false;
		
	return true;
}

bool QJsonTranslator::isEmpty() const
{
	return pLoaded;
}

QString	QJsonTranslator::translate(const char *context, const char *sourceText, const char *disambiguation) const
{
	return translate(context, sourceText, disambiguation, 0);
}

QString QJsonTranslator::translate(const char *context, const char *sourceText, const char *disambiguation, int n) const
{
	// qDebug() << context << sourceText << disambiguation << n;
	if (pLoaded)
	{
		QString tContext, tProperty;

		if (context)
			tContext = context;
		if (disambiguation)
			tProperty = disambiguation;
		if (tProperty.isEmpty() && sourceText)
			tProperty = sourceText;

		if (!tProperty.isEmpty())	
		{
			QVariant result = pLanguageStrip;

			if (!tContext.isEmpty())
				result = result.toMap()[tContext];
			result = result.toMap()[tProperty];

			QString ret = result.toString();
			if (!ret.isEmpty())
				return ret;
		}
	}

	return QString::fromUtf8(sourceText);
}