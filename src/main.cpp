#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuickControls2>
#include <QQuickStyle>
#include <memory>
#include "data.hh"
#include "controller.hh"
#include "view.hh"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif



    QApplication app(argc, argv);

    auto data = new Data();
    auto view = new View();
    auto controller = new Controller(data,view);


    data->fetchData("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&starttime=2021-01-19T09:00:00Z&endtime=2021-01-24T14:00:00Z&timestep=30&parameters=t2m");


    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("view", view);
    engine.rootContext()->setContextProperty("controller", controller);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();

}
