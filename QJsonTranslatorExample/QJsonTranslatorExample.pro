QT       += core gui widgets

TARGET   = QJsonTranslatorExample
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += json.cpp \
			main.cpp \
			qjsontranslator.cpp \
			qjsontranslatorexample.cpp

HEADERS += json.h \
			qjsontranslator.h \
			qjsontranslatorexample.h

FORMS   += qjsontranslatorexample.ui

RESOURCES += qjsontranslatorexample.qrc
