#ifndef QMLREPORTS_H
#define QMLREPORTS_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>
#include <QDebug>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QTextDocumentFragment>
#include <QTime>

#include "qmlreportslogo.h"
#include "qmlreportsfooter.h"
#include "qmlreportscontent.h"
#include "qmlreportselement.h"
#include "qmlreportsconfidential.h"


class QMLReports : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(int resolution READ resolution WRITE setResolution)
    Q_PROPERTY(qreal margins READ margins WRITE setMargins)
    Q_PROPERTY(QMLReportsLogo *logo READ logo WRITE setLogo)
    Q_PROPERTY(QMLReportsFooter *footer READ footer WRITE setFooter)
    Q_PROPERTY(QQmlListProperty<QMLReportsContent> contents READ contents)

public:
    QMLReports(QObject *parent = 0);

    QString fileName() const;
    void setFileName(const QString &fileName);

    int resolution() const;
    void setResolution(const int &resolution);

    qreal margins() const;
    void setMargins(const qreal &margins);

    QMLReportsLogo *logo() const;
    void setLogo(QMLReportsLogo *logo);

    QMLReportsFooter *footer() const;
    void setFooter(QMLReportsFooter *footer);

    QQmlListProperty<QMLReportsContent> contents();
    int contentsCount() const;
    QMLReportsContent *content(int) const;

signals:
    void fileNameChanged();

public slots:
    qreal mm2px(int mm){return mm * 0.039370147 * m_writer->resolution();}
    qreal px2mm(int px){return px / 0.039370147 / m_writer->resolution();}
    void print();
    void import();

private slots:
    void init();
    void addLogo();
    void addFooter();
    void addConfidential();
    void addContent();
    void checkPage();

private:
    QPainter *m_painter;
    QPdfWriter *m_writer;
    QTextCursor *m_cursor;
    QString m_fileName;
    int m_resolution = 300;
    qreal m_margins = 10;
    QMLReportsLogo *m_logo;
    QMLReportsFooter *m_footer;
    QList<QMLReportsContent *> m_contents;
    qreal m_lastY;
    qreal m_heightAvailable;
    qreal m_heightNecessary;
    QString m_totalHtml;
    qreal m_logoHeight, m_footerHeight;
    bool m_contentCompleted;
    int m_nbPage;
};

#endif // QMLREPORTS_H
