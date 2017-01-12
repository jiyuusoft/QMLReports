#include "qmlreportscontent.h"


//QMLReportsContent::QMLReportsContent(QString htmlText, QTextOption::WrapMode wrapMode, QObject *parent)
QMLReportsContent::QMLReportsContent(QString htmlText, QObject *parent)
{
    //setHtmlContent(htmlText);
}

QString QMLReportsContent::color() const
{
    return m_color;
}

void QMLReportsContent::setColor(const QString &a)
{

    if (a != m_color) {
        m_color = a;
        emit colorChanged();
    }
}

QString QMLReportsContent::family() const
{
    return m_family;
}

void QMLReportsContent::setFamily(const QString &a)
{

    if (a != m_family) {
        m_family = a;
        emit familyChanged();
    }
}

int QMLReportsContent::size() const
{
    return m_size;
}

void QMLReportsContent::setSize(const int &a)
{

    if (a != m_size) {
        m_size = a;
        emit sizeChanged();
    }
}

QString QMLReportsContent::style() const
{
    return m_style;
}

void QMLReportsContent::setStyle(const QString &a)
{

    if (a != m_style) {
        m_style = a;
        emit styleChanged();
    }
}

QString QMLReportsContent::weight() const
{
    return m_weight;
}

void QMLReportsContent::setWeight(const QString &a)
{

    if (a != m_weight) {
        m_weight = a;
        emit weightChanged();
    }
}

QString QMLReportsContent::decoration() const
{
    return m_decoration;
}

void QMLReportsContent::setDecoration(const QString &a)
{

    if (a != m_decoration) {
        m_decoration = a;
        emit decorationChanged();
    }
}


QString QMLReportsContent::htmlText() const
{
    return m_htmlText;
}

void QMLReportsContent::setHtmlText(const QString &a)
{

    if (a != m_htmlText) {
        m_htmlText = a;
        emit htmlTextChanged();
    }
}

qreal QMLReportsContent::xOffsetMM() const {return m_xOffsetMM;}
void QMLReportsContent::setXOffsetMM(const qreal &a) {m_xOffsetMM = a;}

qreal QMLReportsContent::yOffsetMM() const {return m_yOffsetMM;}
void QMLReportsContent::setYOffsetMM(const qreal &a) {m_yOffsetMM = a;}

QString QMLReportsContent::align() const {return m_align;}
void QMLReportsContent::setAlign(const QString &a) {m_align = a;}
