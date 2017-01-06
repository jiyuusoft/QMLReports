#include "QMLReportsFooter.h"

QMLReportsFooter::QMLReportsFooter(QString htmlFooter, QTextOption::WrapMode wrapMode, QObject *parent)
{
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);
    textOption.setWrapMode(wrapMode);
    this->setDefaultTextOption(textOption);
    this->setHtml(htmlFooter);
}
