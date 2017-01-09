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

QString QMLReportsContent::size() const
{
    return m_size;
}

void QMLReportsContent::setSize(const QString &a)
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


void QMLReportsContent::setHtmlContent(QString html, QTextOption::WrapMode wrapMode)
{
    QString color = "blue";
    QString family = "verdana";
    QString style = "italic";
    QString size = "30";
    QString weight = "bold";
    QString decoration  = "overline";
    QString styleBegin = tr("<div style='color:%1 ; font-family:%2 ; font-style:%3 ; font-size:%4px ; font-weight:%5 ; text-decoration:%6 ; ' >").arg(color,
                                                                                                                                                            family,
                                                                                                                                                            style,
                                                                                                                                                            size,
                                                                                                                                                            weight,
                                                                                                                                                            decoration);
    QString styleEnd = "</div>";
    QString textHtml = styleBegin + html + styleEnd;
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignJustify);
    textOption.setWrapMode(QTextOption::WordWrap);
    //textOption.setWrapMode(wrapMode);
    this->setDefaultTextOption(textOption);

    this->setHtml(textHtml);
}
