#include "Service.hpp"

#include <QGuiApplication>
#include <sailfishapp.h>

const QString serviceName = QStringLiteral("example.background.application");

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setQuitOnLastWindowClosed(false);

    Service service;
    if (service.initialize()) {
        service.showUi();
        return app->exec();
    } else {
        service.raise();
        return 0;
    }
}
