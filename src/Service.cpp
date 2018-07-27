#include "Service.hpp"

#include <sailfishapp.h>
#include <QQuickView>
#include <QDBusInterface>
#include <QDBusConnectionInterface>
#include <nemonotifications-qt5/notification.h>

#include <QDebug>

static const QString c_dbusServiceName = QStringLiteral("example.background.application");
static const QString c_dbusObjectPath = QStringLiteral("/service");
static const QString c_dbusInterface = QStringLiteral("example.background.application");
static const QString c_dbusMethod = QStringLiteral("showUi");

Service::Service(QObject *parent)
    : QObject(parent)
{
}

void Service::initialize()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();

    dbus.registerObject(c_dbusObjectPath, this, QDBusConnection::ExportScriptableSlots | QDBusConnection::ExportScriptableSignals);
    dbus.registerService(c_dbusServiceName);
}

bool Service::isRegistered()
{
    return QDBusConnection::sessionBus().interface()->isServiceRegistered(c_dbusServiceName);
}

bool Service::raise()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();
    QDBusMessage showUi = QDBusMessage::createMethodCall(
                c_dbusServiceName,
                c_dbusObjectPath,
                c_dbusInterface,
                c_dbusMethod);
    return dbus.send(showUi);
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

    removeNotification();
}

void Service::onUiDestroyed()
{
    disconnect(m_view, 0, 0, 0);
    m_view = nullptr;

    showNotification();
}

void Service::onUiClosing()
{
    m_view->destroy();
    m_view->deleteLater();
}

void Service::showNotification()
{
    qWarning() << Q_FUNC_INFO;

    Notification n;
    n.setReplacesId(m_notificationId);
    n.setRemoteAction(Notification::remoteAction(
                          QStringLiteral("default"),
                          QStringLiteral("test"),
                          c_dbusServiceName,
                          c_dbusObjectPath,
                          c_dbusInterface,
                          c_dbusMethod)
                       );
    n.setBody(QStringLiteral("Example body"));
    n.setPreviewBody(n.body());
    n.setSummary(QStringLiteral("Example summary"));
    n.setPreviewSummary(n.summary());
    n.publish();
    m_notificationId = n.replacesId();
}

void Service::removeNotification()
{
    if (m_notificationId == 0) {
        return;
    }

    Notification n;
    n.setReplacesId(m_notificationId);
    n.close();

    m_notificationId = 0;
}
