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
#include <QTextBlockFormat>
#include <QAbstractTextDocumentLayout>
#include <QTextDocumentFragment>
#include <QTime>
#include <QPrinter>
#include <QStringList>

#include "qmlreportsheader.h"
#include "qmlreportsfooter.h"
#include "qmlreportscontent.h"
#include "qmlreportselement.h"
#include "qmlreportsconfidential.h"


class QMLReports : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString model READ model WRITE setModel)
    Q_PROPERTY(QString modelStyle READ modelStyle WRITE setModelStyle)
    Q_PROPERTY(int resolution READ resolution WRITE setResolution)
    Q_PROPERTY(qreal margins READ margins WRITE setMargins)
    Q_PROPERTY(QMLReportsHeader *header READ header WRITE setHeader)
    Q_PROPERTY(QMLReportsFooter *footer READ footer WRITE setFooter)
    Q_PROPERTY(QQmlListProperty<QMLReportsContent> contents READ contents)
    Q_PROPERTY(QVariantList dataModel READ dataModel WRITE setDataModel)  //change to modelData
    Q_PROPERTY(bool confidential READ confidential WRITE setConfidential)

public:
    QMLReports(QObject *parent = 0);

    QString fileName() const;
    void setFileName(const QString &fileName);

    QString model() const;
    void setModel(const QString &model);

    QString modelStyle() const;
    void setModelStyle(const QString &modelStyle);

    int resolution() const;
    void setResolution(const int &resolution);

    qreal margins() const;
    void setMargins(const qreal &margins);

    QMLReportsHeader *header() const;
    void setHeader(QMLReportsHeader *header);

    QMLReportsFooter *footer() const;
    void setFooter(QMLReportsFooter *footer);

    QQmlListProperty<QMLReportsContent> contents();
    int contentsCount() const;
    QMLReportsContent *content(int) const;

    QVariantList dataModel() const;
    void setDataModel(const QVariantList &dataModel);

    bool confidential() const;
    void setConfidential(const bool &confidential);

signals:
    void fileNameChanged();

public slots:
    qreal mm2px(int mm){return mm * 0.039370147 * m_writer->resolution();}
    qreal px2mm(int px){return px / 0.039370147 / m_writer->resolution();}
    void print();
    void import();
    QString setFormat(QMLReportsElement *element);
    void test();

private slots:
    void createHeader();
    void createFooter();
    void createConfidential();
    void addContent();

private:
    QPdfWriter *m_writer = 0;
    QRectF m_rectContent;
    QString m_fileName;
    QString m_model = "";
    QVariantList m_dataModel;
    QString m_modelStyle;

    bool m_confidential = false;

    int m_resolution = 300;
    qreal m_margins = 10;
    QMLReportsHeader *m_qmlHeader = 0;
    QMLReportsFooter *m_qmlFooter = 0;
    QList<QMLReportsContent *> m_contents; // how initialize ???
    QList<QStringList *> m_datasModel;
    qreal m_lastY;
    qreal m_heightAvailable;
    qreal m_heightNecessary;
    QString m_totalHtml;
    qreal m_logoHeight, m_qmlFooterHeight;
    bool m_contentCompleted = false;
    int m_nbPage = 0;
    int m_alreadyPaint = 0;

    qreal m_beginContentY;
    qreal m_endContentY;


    ///to create report
    QTextDocument *m_tdHeader;
    QTextDocument *m_tdFooter;
    QTextDocument *m_tdConfidential;
    QRectF m_rectPrinter;
    QSizeF m_headerSize;
    QSizeF m_footerSize;
};

#endif // QMLREPORTS_H
