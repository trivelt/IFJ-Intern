TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += cwiczenie2.C
HEADERS += cwiczenie2.h

INCLUDEPATH += /usr/local/include/root
LIBS += -L/usr/local/lib/root -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic


QMAKE_CXXFLAGS += -std=c++11
