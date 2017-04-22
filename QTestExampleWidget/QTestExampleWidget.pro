QT       += core gui widgets

TARGET   = QTestExampleWidget
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
			qtestexamplewidget.cpp \
			qvolumemeter.cpp

HEADERS += qtestexamplewidget.h \
			qvolumemeter.h

FORMS   += qtestexamplewidget.ui

RESOURCES += qtestexamplewidget.qrc
