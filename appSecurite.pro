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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/release/ -lcryptoCielTest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/debug/ -lcryptoCielTest
else:unix: LIBS += -L$$PWD/../../CryptoCielLIB/x64/ -lcryptoCielTest

INCLUDEPATH += $$PWD/../../CryptoCiel
DEPENDPATH += $$PWD/../../CryptoCiel

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/release/libcryptoCielTest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/debug/libcryptoCielTest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/release/cryptoCielTest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/debug/cryptoCielTest.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/libcryptoCielTest.a

win32: LIBS += -L$$PWD/../../CryptoCielLIB/x64/Release/ -lcryptoCielTest

INCLUDEPATH += $$PWD/../../CryptoCielLIB
DEPENDPATH += $$PWD/../../CryptoCielLIB

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/Release/cryptoCielTest.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/Release/libcryptoCielTest.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/release/ -lcryptoCielTest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/debug/ -lcryptoCielTest

INCLUDEPATH += $$PWD/../../CryptoCielLIB
DEPENDPATH += $$PWD/../../CryptoCielLIB

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/release/libcryptoCielTest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/debug/libcryptoCielTest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/release/cryptoCielTest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/debug/cryptoCielTest.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cryptopp/x64/Output/release/ -lcryptlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../cryptopp/x64/Output/debug/ -lcryptlib
else:unix: LIBS += -L$$PWD/../../cryptopp/x64/Output/ -lcryptlib

INCLUDEPATH += $$PWD/../../cryptopp/x64/Output/Release
DEPENDPATH += $$PWD/../../cryptopp/x64/Output/Release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/release/libcryptlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/debug/libcryptlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/release/cryptlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/debug/cryptlib.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/libcryptlib.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/release/ -lcryptoCielTest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/debug/ -lcryptoCielTest
else:unix: LIBS += -L$$PWD/../../CryptoCielLIB/x64/ -lcryptoCielTest

INCLUDEPATH += $$PWD/../../CryptoCielLIB
DEPENDPATH += $$PWD/../../CryptoCielLIB

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/release/libcryptoCielTest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/debug/libcryptoCielTest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/release/cryptoCielTest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/debug/cryptoCielTest.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../CryptoCielLIB/x64/libcryptoCielTest.a

win32: LIBS += -L$$PWD/../../cryptopp/x64/Output/Release/ -lcryptlib

INCLUDEPATH += $$PWD/../../cryptopp
DEPENDPATH += $$PWD/../../cryptopp

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/Release/cryptlib.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../cryptopp/x64/Output/Release/libcryptlib.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/release/ -lcryptoCielTest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CryptoCielLIB/x64/debug/ -lcryptoCielTest
else:unix: LIBS += -L$$PWD/../../CryptoCielLIB/x64/ -lcryptoCielTest

INCLUDEPATH += $$PWD/../../CryptoCielLIB
DEPENDPATH += $$PWD/../../CryptoCielLIB
