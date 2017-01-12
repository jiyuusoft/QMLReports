#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlreports.h"
#include "qmlreportsreport.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    qmlRegisterType<QMLReportsReport>("QMLReports", 1, 0, "Report");
    qmlRegisterType<QMLReportsContent>("QMLReports", 1, 0, "ReportContent");
    qmlRegisterType<QMLReportsFooter>("QMLReports", 1, 0, "ReportFooter");
    qmlRegisterType<QMLReportsLogo>("QMLReports", 1, 0, "ReportLogo");
    qmlRegisterType<QMLReports>("QMLReports", 1, 0, "Reports");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
