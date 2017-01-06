#include "qmlreportsheader.h"

QMLReportsHeader::QMLReportsHeader(QPainter *painter, QObject *parent) : QObject(parent), m_painter(painter)
{
    m_device = m_painter->device();
    qDebug() << "DEVICE DPI" << m_device->logicalDpiX();
    qDebug() << "DEVICE HEIGHT MM" << m_device->heightMM() << mm2px(m_device->heightMM());
    qDebug() << "DEVICE HEIGHT PIX" << m_device->height();
    qDebug() << "DEVICE WIDTH MM" << m_device->widthMM();
    qDebug() << "DEVICE WIDTH PIX" << m_device->width();

}


void QMLReportsHeader::setPen(QString color)
{
    m_painter->setPen(QColor(color));
}

void QMLReportsHeader::setPen(Qt::GlobalColor color)
{
    m_painter->setPen(color);
}

/*
void QMLReportsHeader::setStyle(QString font,
                                    int size,
                                    bool weight,
                                    bool italic,
                                    QString color)
{

}

void QMLReportsHeader::setStyle(QString font,
                                    int size,
                                    bool weight,
                                    bool italic,
                                    Qt::GlobalColor)
{

}
*/
void QMLReportsHeader::setRect(qreal x, qreal y, qreal h, qreal w)
{
    m_rect.setRect(x, y, h, w);
}

qreal QMLReportsHeader::bottomMM()
{
    qreal bottomRect = m_rect.bottom();
    qreal bottomLogo = m_xy_LogoTopLeft.y() + m_logo.height();

    if (bottomRect > bottomLogo) return px2mm(bottomRect);
    else return px2mm(bottomLogo)+5;
}


void QMLReportsHeader::drawTopLeftImage(QString img, qreal offsetMM)
{
    m_logo.load(img);
    m_xy_LogoTopLeft.setX(m_rect.x()+mm2px(offsetMM));
    m_xy_LogoTopLeft.setY(m_rect.y()+mm2px(offsetMM));
    m_painter->drawImage(m_xy_LogoTopLeft, QImage(m_logo));

    qDebug() << "BOTTOM depuis Class" << bottomMM();
}

void QMLReportsHeader::drawCenterImage(QString img)
{
    m_logo.load(img);
    qreal xCenterRect = m_rect.x() + m_rect.width()/2;
    qreal yCenterRect = m_rect.y() + m_rect.height()/2;
    m_xy_LogoTopLeft.setX(xCenterRect-m_logo.width()/2);
    m_xy_LogoTopLeft.setY(yCenterRect-m_logo.height()/2);
    m_painter->drawImage(m_xy_LogoTopLeft, QImage(m_logo));
}

void QMLReportsHeader::drawRect()
{
    m_painter->drawRect(m_rect);
}
