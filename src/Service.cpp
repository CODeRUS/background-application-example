#include "Service.hpp"
#include <QDBusInterface>
#include <QDBusConnectionInterface>

Service::Service(QObject *parent)
    : QObject(parent)
    , m_view(nullptr)
{
}

bool Service::initialize()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();
    if (dbus.interface()->isServiceRegistered("example.background.application")) {
        return false;
    }

    dbus.registerObject("/service", this, QDBusConnection::ExportScriptableSlots | QDBusConnection::ExportScriptableSignals);
    dbus.registerService("example.background.application");

    return true;
}

void Service::raise()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();
    QDBusMessage showUi = QDBusMessage::createMethodCall(
                "example.background.application",
                "/service",
                "example.background.application",
                "showUi");
    dbus.call(showUi, QDBus::NoBlock);
}

void Service::showUi()
{
    if (m_view) {
        return;
    }

    m_view = SailfishApp::createView();
    m_view->setSource(SailfishApp::pathTo("qml/background-application-example.qml"));
    m_view->showFullScreen();

    connect(m_view, &QQuickView::destroyed, this, &Service::onUiDestroyed);
    connect(m_view, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(onUiClosing())); // Yes, it's PITA, but no workaround
}

void Service::onUiDestroyed()
{
    disconnect(m_view, 0, 0, 0);
    m_view = nullptr;
}

void Service::onUiClosing()
{
    m_view->destroy();
    m_view->deleteLater();
}
