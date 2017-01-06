#include "qmlreportscontent.h"


QMLReportsContent::QMLReportsContent(QString htmlText, QTextOption::WrapMode wrapMode, QObject *parent)
{
    setHtmlContent(htmlText, wrapMode);
}

void QMLReportsContent::setHtmlContent(QString html, QTextOption::WrapMode wrapMode)
{
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignJustify);
    textOption.setWrapMode(wrapMode);
    this->setDefaultTextOption(textOption);
    this->setHtml(html);
}
