#include "QMLReportsFooter.h"

QMLReportsFooter::QMLReportsFooter(QObject *parent)
{

}

QString QMLReportsFooter::color() const
{
    return m_color;
}

void QMLReportsFooter::setColor(const QString &a)
{

    if (a != m_color) {
        m_color = a;
        emit colorChanged();
    }
}

QString QMLReportsFooter::family() const
{
    return m_family;
}

void QMLReportsFooter::setFamily(const QString &a)
{

    if (a != m_family) {
        m_family = a;
        emit familyChanged();
    }
}

int QMLReportsFooter::size() const
{
    return m_size;
}

void QMLReportsFooter::setSize(const int &a)
{

    if (a != m_size) {
        m_size = a;
        emit sizeChanged();
    }
}

QString QMLReportsFooter::style() const
{
    return m_style;
}

void QMLReportsFooter::setStyle(const QString &a)
{

    if (a != m_style) {
        m_style = a;
        emit styleChanged();
    }
}

QString QMLReportsFooter::weight() const
{
    return m_weight;
}

void QMLReportsFooter::setWeight(const QString &a)
{

    if (a != m_weight) {
        m_weight = a;
        emit weightChanged();
    }
}

QString QMLReportsFooter::decoration() const
{
    return m_decoration;
}

void QMLReportsFooter::setDecoration(const QString &a)
{

    if (a != m_decoration) {
        m_decoration = a;
        emit decorationChanged();
    }
}


QString QMLReportsFooter::htmlText() const
{
    return m_htmlText;
}

void QMLReportsFooter::setHtmlText(const QString &a)
{

    if (a != m_htmlText) {
        m_htmlText = a;
        emit htmlTextChanged();
    }
}

qreal QMLReportsFooter::xOffsetMM() const {return m_xOffsetMM;}
void QMLReportsFooter::setXOffsetMM(const qreal &a) {m_xOffsetMM = a;}

qreal QMLReportsFooter::yOffsetMM() const {return m_yOffsetMM;}
void QMLReportsFooter::setYOffsetMM(const qreal &a) {m_yOffsetMM = a;}

QString QMLReportsFooter::align() const {return m_align;}
void QMLReportsFooter::setAlign(const QString &a) {m_align = a;}

