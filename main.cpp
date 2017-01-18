#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QQmlContext>
#include <QDebug>
#include "qmlreports.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QStandardPaths *standardPath = nullptr;
    QString dataLocation;


#ifdef Q_OS_ANDROID
    dataLocation = standardPath->standardLocations(QStandardPaths::DataLocation)[1];
#else
    dataLocation = standardPath->standardLocations(QStandardPaths::DataLocation)[0];
#endif

    QMLReports report;
    report.import();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataLocation", dataLocation);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
