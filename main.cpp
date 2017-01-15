#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QQmlContext>
#include "qmlreportsreport.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QStandardPaths *standardPath;


#ifdef Q_OS_ANDROID
    QString dataLocation = standardPath->standardLocations(QStandardPaths::DataLocation)[1];
#else
    QString dataLocation = standardPath->standardLocations(QStandardPaths::DataLocation)[0];
#endif



    qmlRegisterType<QMLReportsReport>("QMLReports", 1, 0, "Report");
    qmlRegisterType<QMLReportsContent>("QMLReports", 1, 0, "ReportContent");
    qmlRegisterType<QMLReportsFooter>("QMLReports", 1, 0, "ReportFooter");
    qmlRegisterType<QMLReportsLogo>("QMLReports", 1, 0, "ReportLogo");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataLocation", dataLocation);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
