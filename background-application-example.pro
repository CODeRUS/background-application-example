TARGET = background-application-example

QT += dbus
CONFIG += sailfishapp
PKGCONFIG += nemonotifications-qt5

INCLUDEPATH += c:\SailfishOS\mersdk\targets\SailfishOS-2.2.0.29-armv7hl\usr\include\

SOURCES += \
    src/background-application-example.cpp \
    src/Service.cpp

HEADERS += \
    src/Service.hpp

DISTFILES += \
    qml/background-application-example.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    background-application-example.desktop

OTHER_FILES += \
    rpm/background-application-example.spec

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256


systemd.files = systemd/dbus-example.background.application.service
systemd.path = /usr/lib/systemd/user
INSTALLS += systemd

dbus.files = dbus/example.background.application.service
dbus.path = /usr/share/dbus-1/services
INSTALLS += dbus
