TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11


INCLUDEPATH += /usr/local/include/root
LIBS += -L/usr/local/lib/root -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic

