QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

#set libModehere
libMode = true
libFolder = $$PWD/libFolder
$$libMode {
DESTDIR= $$libFolder
OBJECTS_DIR = $$libFolder
MOC_DIR = $$libFolder
RCC_DIR = $$libFolder
UI_DIR = $$libFolder
DEFINES += "LIBMODE=1"
} else {
DEFINES += "LIBMODE=0"}


INCLUDEPATH += /home/ole/Desktop/myCode/qt/ERLayout/sharedEnums \

SOURCES += \
    compressedair.cpp \
    connectca.cpp \
    controlpanelca.cpp \
    main.cpp \
    screenca.cpp \
    settingsca.cpp

HEADERS += \
    compressedair.h \
    controlpanelca.h \
    enumsca.h \
    screenca.h \
    settingsca.h

FORMS += \
    compressedair.ui \
    controlpanelca.ui \
    screenca.ui \
    settingsca.ui

RESOURCES += \
    graphics/resources.qrc
