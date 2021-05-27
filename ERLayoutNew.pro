QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


mainfolderCA = /home/ole/myCode/qt/ERLayout/CompressedAir
mainfolderCW = /home/ole/myCode/qt/ERLayout/CoolingWater

libFolderCA = $$mainfolderCA/libFolder
libFolderCW = $$mainfolderCW/libFolder

objectFileListCA = $$files($$libFolderCA/*.o)
objectFileListCA-= $$libFolderCA/main.o

objectFilesCW = $$files($$libFolderCW/*.o)
objectFilesCW -= $$libFolderCW/main.o

INCLUDEPATH +=  $$mainfolderCA \
                $$libFolderCA \
                $$mainfolderCW \
                $$libFolderCW \
                /home/ole/Desktop/myCode/qt/ERLayout/sharedEnums \
                /home/ole/Desktop/myCode/qt/ERLayout/sharedSource


LIBS += $$objectFileListCA \
        $$objectFilesCW \
        /home/ole/myCode/qt/ERLayout/sharedLibraries/QCustomPlot/myLibTrue/libmylib.a

SOURCES += \
    ../ERLayout/sharedSource/enginecontrol.cpp \
    datatable.cpp \
           main.cpp \
mainwindow.cpp \
           simcontrol.cpp

HEADERS += \
    ../ERLayout/sharedSource/enginecontrol.h \
    datatable.h \
mainwindow.h \
    simcontrol.h


FORMS += \
    ../ERLayout/sharedSource/enginecontrol.ui \
    datatable.ui \
    mainwindow.ui \
    simcontrol.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/release/ -lmylib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/debug/ -lmylib
#else:unix: LIBS += -L$$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/ -lmylib

#INCLUDEPATH += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug
#DEPENDPATH += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug
#LIBS += /home/ole/myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/libmylib.a
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/release/ -lmylib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/debug/ -lmylib
#else:unix: LIBS += -L$$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/ -lmylib

#INCLUDEPATH += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug
#DEPENDPATH += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/release/libmylib.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/debug/libmylib.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/release/mylib.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/debug/mylib.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../../../myCode/qt/ERLayout/sharedLibraries/QCustomPlot/build-myLib-Desktop-Debug/libmylib.a
