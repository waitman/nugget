QT       += core gui widgets webkitwidgets

TARGET = nugget
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

#RESOURCES     = disposera.qrc

HEADERS  += mainwindow.h

FORMS    += nugget.ui 

#debugging
#QMAKE_CXXFLAGS += -g

#FreeBSD
unix {
	LIBS 		+= -L/usr/local/lib 
	INCLUDES	+= -I/usr/local/include 
}

