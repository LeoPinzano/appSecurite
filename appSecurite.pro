QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../../Seq1_Act05_chiffrementCpp/CryptoCiel/x64/Release/ -lcryptoCielTest

INCLUDEPATH += $$PWD/../../Seq1_Act05_chiffrementCpp/CryptoCiel
DEPENDPATH += $$PWD/../../Seq1_Act05_chiffrementCpp/CryptoCiel

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../Seq1_Act05_chiffrementCpp/CryptoCiel/x64/Release/cryptoCielTest.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../Seq1_Act05_chiffrementCpp/CryptoCiel/x64/Release/libcryptoCielTest.a

win32: LIBS += -L$$PWD/../../Seq1_Act05_chiffrementCpp/cryptopp/x64/Output/Release/ -lcryptlib

INCLUDEPATH += $$PWD/../../Seq1_Act05_chiffrementCpp/cryptopp
DEPENDPATH += $$PWD/../../Seq1_Act05_chiffrementCpp/cryptopp

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../Seq1_Act05_chiffrementCpp/cryptopp/x64/Output/Release/cryptlib.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../Seq1_Act05_chiffrementCpp/cryptopp/x64/Output/Release/libcryptlib.a
