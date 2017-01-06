#include "qmlreportslogo.h"

QMLReportsLogo::QMLReportsLogo(QString htmlLogo, QTextOption::WrapMode wrapMode, QObject *parent)
{
    setLogo(htmlLogo, wrapMode);
}

void QMLReportsLogo::setLogo(QString htmlLogo, QTextOption::WrapMode wrapMode)
{
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignRight);
    textOption.setWrapMode(wrapMode);
    this->setDefaultTextOption(textOption);
    this->setHtml(htmlLogo);
}
