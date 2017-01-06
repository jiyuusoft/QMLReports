#include "qmlreports.h"

QMLReports::QMLReports(QObject *parent) : QObject(parent)
{

}

QString QMLReports::fileName() const
{
    return m_fileName;
}

void QMLReports::setFileName(const QString &a)
{

    if (a != m_fileName) {
        m_fileName = a;
        emit fileNameChanged();
    }
}

QString QMLReports::logoHtml() const
{
    return m_logoHtml;
}

void QMLReports::setLogoHtml(const QString &a)
{

    if (a != m_logoHtml) {
        m_logoHtml = a;
        emit logoHtmlChanged();
    }
}

QString QMLReports::footerHtml() const
{
    return m_footerHtml;
}

void QMLReports::setFooterHtml(const QString &a)
{

    if (a != m_footerHtml) {
        m_footerHtml = a;
        emit footerHtmlChanged();
    }
}


QString QMLReports::contentHtml1() const
{
    return m_contentHtml1;
}

void QMLReports::setContentHtml1(const QString &a)
{

    if (a != m_contentHtml1) {
        m_contentHtml1 = a;
        emit contentHtml1();
    }
}

QString QMLReports::contentHtml2() const
{
    return m_contentHtml2;
}

void QMLReports::setContentHtml2(const QString &a)
{

    if (a != m_contentHtml2) {
        m_contentHtml2 = a;
        emit contentHtml2();
    }
}



/* GENERATION DU RAPPORT */
void QMLReports::test()
{
    QString fileName = m_fileName;
    QMLReportsReport report(fileName);

    QString html1 = m_contentHtml1;
    QString html2=  m_contentHtml2;

    QMLReportsLogo logo(m_logoHtml);
    QMLReportsContent qmlContent1(html1);
    QMLReportsContent qmlContent2(html2);
    QMLReportsFooter qmlFooter(m_footerHtml);

    report.addLogo(&logo, -5, -5);
    report.addFooter(&qmlFooter, 0, 5);

    report.addContent(&qmlContent1);
    report.addContent(&qmlContent2);

    report.end();
    QDesktopServices::openUrl(QUrl("file:"+fileName));
}
