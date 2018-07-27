#include "Service.hpp"

#include <QGuiApplication>
#include <sailfishapp.h>

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));

    if (app->arguments().last() == QStringLiteral("activate")) {
        if (!Service::isRegistered()) {
            app->setQuitOnLastWindowClosed(false);

            Service service;
            service.initialize();
            service.showUi();

            return app->exec();
        } else {
            return 1;
        }
    } else {
        if (Service::raise()) {
            return 0;
        } else {
            return 1;
        }
    }
}
