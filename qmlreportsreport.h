#ifndef QMLREPORTSREPORT_H
#define QMLREPORTSREPORT_H

#include <QObject>
#include <QPainter>
#include <QPdfWriter>
#include <QDebug>
#include <QAbstractTextDocumentLayout>

#include "qmlreportscontent.h"
#include "qmlreportslogo.h"
#include "qmlreportsfooter.h"

class QMLReportsReport : public QObject, public QPainter
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    //Q_PROPERTY(QTextDocument content READ content WRITE setContent NOTIFY contentChanged)
    //Q_PROPERTY(QObject logo READ logo WRITE setLogo NOTIFY logoChanged)

public:
    explicit QMLReportsReport(QString fileName="", qreal margin=10, qreal resolution=300);

signals:
    void fileNameChanged();
    //void contentChanged();
    //void logoChanged();

public slots:
    /*    QML   */
    QString fileName() const;
    void setFileName(const QString &a);

    //QTextDocument content() const;   // soit travailler avec un QString danc c++ et objectName dans QML soit avec un QuickItem ?
    //void setContent(const QTextDocument &a);

    //QObject logo() const;
    //void setLogo(const QObject &a);

    /*    QML   */

    qreal mm2px(int mm){return mm * 0.039370147 * m_writer->resolution();}
    qreal px2mm(int px){return px / 0.039370147 / m_writer->resolution();}
    qreal widthMM();
    void setResolution(qreal resolution);
    void addPage();

    void addLogo(QMLReportsLogo *logo, qreal xOffsetMM=0, qreal yOffsetMM=0);
    void addContent(QMLReportsContent *content, qreal xOffsetMM=0, qreal yOffsetMM=0);
    void addFooter(QMLReportsFooter *footer, qreal xOffsetMM=0, qreal yOffsetMM=0);

public:
    QPainter *painter;
    QMLReportsContent *m_content;
    QMLReportsLogo *m_logo;
    QMLReportsFooter *m_footer;
    qreal m_xLogoOffset;
    qreal m_yLogoOffset;
    qreal m_xFooterOffset;
    qreal m_yFooterOffset;
    qreal m_totalHeightDoc;
    qreal m_heightContentAvailable;

private:
    QPdfWriter *m_writer;
    QString m_fileName;
    qreal m_margin;
    qreal m_resolution;
    QRectF *m_rectContent;
    int m_nbPage=1;
    qreal m_totalContent;
    qreal m_logoTotalHeight;


    /*   QML   */
    QObject m_qmlLogo;
    QTextDocument m_qmlContent;
};

#endif // QMLREPORTSREPORT_H
