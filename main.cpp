#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlreports.h"
#include "qmlreportsreport.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    qmlRegisterType<QMLReportsReport>("QMLReports", 1, 0, "Report");
    qmlRegisterType<QMLReports>("QMLReports", 1, 0, "Reports");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
