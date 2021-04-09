#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuickControls2>
#include <QQuickStyle>
#include <memory>
#include "data.hh"
#include "controller.hh"
#include "backend.h"
#include <typeinfo>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QString OperatingSystem;
#ifdef linux
    OperatingSystem = "LINUX";
#elif defined(_WIN32)
    OperatingSystem = "WINDOWS";
#endif

    QApplication app(argc, argv);

    app.setWindowIcon(QIcon("../kumivene-solutions/res/stonks.JPG"));

    auto backend = std::make_shared<Backend>();
    auto controller = std::make_shared<Controller>(backend);

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("controller", controller.get());
    engine.rootContext()->setContextProperty("OS", OperatingSystem);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    controller->setView(engine.rootObjects()[0]);
    return app.exec();
}
