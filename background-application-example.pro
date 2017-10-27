TARGET = background-application-example

QT += dbus
CONFIG += sailfishapp

SOURCES += \
    src/background-application-example.cpp \
    src/Service.cpp

DISTFILES += \
    qml/background-application-example.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    background-application-example.desktop

OTHER_FILES += \
    rpm/background-application-example.spec

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

HEADERS += \
    src/Service.hpp

