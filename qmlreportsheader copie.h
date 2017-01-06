#ifndef QMLREPORTSHEADER_H
#define QMLREPORTSHEADER_H

#include <QObject>
#include <QDebug>
#include <QPainter>
#include <QPdfWriter>
#include <QFile>
#include <QColor>

#define COLOR_YELLOW Qt::yellow

class QMLReportsHeader : public QObject
{
    Q_OBJECT
public:
    explicit QMLReportsHeader(QPainter *painter=Q_NULLPTR, QObject *parent = Q_NULLPTR);

private slots:

public slots:
    //void setPainter(QPainter *painter);
    qreal mm2px(int mm){return mm * 0.039370147 * m_device->logicalDpiX();}
    qreal px2mm(int px){return px / 0.039370147 / m_device->logicalDpiX();}


    void setPen(QString color);
    void setPen(Qt::GlobalColor color);
    /*
    void setStyle(QString font="verdana",
                      int size=10,
                      bool weight=false,
                      bool italic=false,
                      QString color="black");
    void setStyle(QString font="verdana",
                      int size=10,
                      bool weight=false,
                      bool italic=false,
                      Qt::GlobalColor color=Qt::black);
                      */
    void setRect(qreal x, qreal y, qreal h, qreal w);

    qreal bottomMM();

    void drawTopLeftImage(QString img, qreal offsetMM=0);
    void drawCenterImage(QString img);
    void drawRect();


private:
    QPaintDevice *m_device;
    QPainter *m_painter;
    QRectF m_rect;

    // logo
    QPointF m_xy_LogoTopLeft;
    QImage m_logo;

};


#endif // QMLREPORTSHEADER_H
