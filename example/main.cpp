#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QQmlContext>
#include <QDebug>
#include <QPdfDocument>
#include <QDesktopServices>
#include <Qurl>
#include "../qmlreports.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QStandardPaths *standardPath = nullptr;
    QString dataLocation;

    QPdfDocument pdfDoc;
    pdfDoc.load("/Users/charlie/Documents/test.pdf");
    const auto documentTitle = pdfDoc.metaData(QPdfDocument::Title).toString();
    const auto pageCount = pdfDoc.pageCount();
    QImage img = pdfDoc.render(0, QSizeF(2100, 2970));




#ifdef Q_OS_ANDROID
    dataLocation = standardPath->standardLocations(QStandardPaths::DataLocation)[1];
#else
    dataLocation = standardPath->standardLocations(QStandardPaths::DataLocation)[0];

#endif

    QString file("/Users/charlie/toto.png");
    //qDebug() << file << documentTitle << pageCount;
    img.save(file);
    //QDesktopServices::openUrl(QUrl("file:"+file));


    QMLReports report;
    //report.import();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataLocation", dataLocation);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
