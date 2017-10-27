#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <QObject>
#include <QQuickView>
#include <sailfishapp.h>


class Service : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "example.background.application")
public:
    explicit Service(QObject *parent = 0);
    bool initialize();
    void raise();

signals:

public slots:
    Q_SCRIPTABLE void showUi();

private slots:
    void onUiDestroyed();
    void onUiClosing();

private:
    QQuickView *m_view;
};

#endif // SERVICE_HPP
