# Qt project file - qmake uses his to generate a Makefile

QT       += core gui

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QwtExample

LIBS += -lqwt -lm -lwiringPi

HEADERS += window.h adcreader.h mcp3008Spi.h

# WateringThread.h

SOURCES += main.cpp window.cpp adcreader.cpp mcp3008Spi.cpp

# WateringThread.cpp
