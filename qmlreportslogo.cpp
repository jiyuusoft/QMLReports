#include "qmlreportslogo.h"

QMLReportsLogo::QMLReportsLogo(QObject *parent)
{

}


QString QMLReportsLogo::color() const
{
    return m_color;
}

void QMLReportsLogo::setColor(const QString &a)
{

    if (a != m_color) {
        m_color = a;
        emit colorChanged();
    }
}

QString QMLReportsLogo::family() const
{
    return m_family;
}

void QMLReportsLogo::setFamily(const QString &a)
{

    if (a != m_family) {
        m_family = a;
        emit familyChanged();
    }
}

int QMLReportsLogo::size() const
{
    return m_size;
}

void QMLReportsLogo::setSize(const int &a)
{

    if (a != m_size) {
        m_size = a;
        emit sizeChanged();
    }
}

QString QMLReportsLogo::style() const
{
    return m_style;
}

void QMLReportsLogo::setStyle(const QString &a)
{

    if (a != m_style) {
        m_style = a;
        emit styleChanged();
    }
}

QString QMLReportsLogo::weight() const
{
    return m_weight;
}

void QMLReportsLogo::setWeight(const QString &a)
{

    if (a != m_weight) {
        m_weight = a;
        emit weightChanged();
    }
}

QString QMLReportsLogo::decoration() const
{
    return m_decoration;
}

void QMLReportsLogo::setDecoration(const QString &a)
{

    if (a != m_decoration) {
        m_decoration = a;
        emit decorationChanged();
    }
}


QString QMLReportsLogo::htmlText() const
{
    return m_htmlText;
}

void QMLReportsLogo::setHtmlText(const QString &a)
{

    if (a != m_htmlText) {
        m_htmlText = a;
        emit htmlTextChanged();
    }
}

qreal QMLReportsLogo::xOffsetMM() const {return m_xOffsetMM;}
void QMLReportsLogo::setXOffsetMM(const qreal &a) {m_xOffsetMM = a;}

qreal QMLReportsLogo::yOffsetMM() const {return m_yOffsetMM;}
void QMLReportsLogo::setYOffsetMM(const qreal &a) {m_yOffsetMM = a;}

bool QMLReportsLogo::center() const {return m_center;}
void QMLReportsLogo::setCenter(const bool &a) {m_center = a;}

QString QMLReportsLogo::align() const {return m_align;}
void QMLReportsLogo::setAlign(const QString &a) {m_align = a;}

