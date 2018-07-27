#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <QObject>

class QQuickView;
class Service : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "example.background.application")
public:
    explicit Service(QObject *parent = 0);
    void initialize();

    static bool isRegistered();
    static bool raise();

signals:

public slots:
    Q_SCRIPTABLE void showUi();

private slots:
    void onUiDestroyed();
    void onUiClosing();

private:
    void showNotification();
    void removeNotification();

    QQuickView *m_view = nullptr;
    quint32 m_notificationId = 0;
};

#endif // SERVICE_HPP
