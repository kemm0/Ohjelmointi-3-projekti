#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuickControls2>
#include <QQuickStyle>
#include "data.hh"
#include "view.hh"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif



    QApplication app(argc, argv);

    auto data = new Data;


    data->fetchDataFinGrid("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&timestep=30&parameters=t2m,ws_10min,n_man");


    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;
    View view;
    engine.rootContext()->setContextProperty("view", &view);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();

}
