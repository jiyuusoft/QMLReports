#ifndef QMLREPORTS_H
#define QMLREPORTS_H

#include <QObject>
#include <QUrl>
#include <QDesktopServices>

#include "qmlreportsreport.h"
#include "qmlreportsfooter.h"
#include "qmlreportscontent.h"
#include "qmlreportslogo.h"


class QMLReports : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString logoHtml READ logoHtml WRITE setLogoHtml NOTIFY logoHtmlChanged)
    Q_PROPERTY(QString footerHtml READ footerHtml WRITE setFooterHtml NOTIFY footerHtmlChanged)
    Q_PROPERTY(QString contentHtml1 READ contentHtml1 WRITE setContentHtml1 NOTIFY contentHtml1Changed)
    Q_PROPERTY(QString contentHtml2 READ contentHtml2 WRITE setContentHtml2 NOTIFY contentHtml2Changed)


public:
    explicit QMLReports(QObject *parent = 0);

    QString fileName() const;
    void setFileName(const QString &a);

    QString logoHtml() const;
    void setLogoHtml(const QString &a);

    QString footerHtml() const;
    void setFooterHtml(const QString &a);

    QString contentHtml1() const;
    void setContentHtml1(const QString &a);

    QString contentHtml2() const;
    void setContentHtml2(const QString &a);

signals:
    void fileNameChanged();
    void logoHtmlChanged();
    void footerHtmlChanged();
    void contentHtml1Changed();
    void contentHtml2Changed();

public slots:
    //void test();

private:
    QString m_fileName;
    QString m_logoHtml;
    QString m_footerHtml;
    QString m_contentHtml1;
    QString m_contentHtml2;


};

#endif // QMLREPORTS_H
