#ifndef QMLREPORTSCONTENT_H
#define QMLREPORTSCONTENT_H

#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextOption>

class QMLReportsContent : public QTextDocument
{
    Q_OBJECT

public:
    explicit QMLReportsContent(QString htmlText="", QTextOption::WrapMode wrapMode = QTextOption::WordWrap, QObject *parent = Q_NULLPTR);


public slots:
    void setHtmlContent(QString html, QTextOption::WrapMode wrapMode=QTextOption::WordWrap);

};


#endif // QMLREPORTSCONTENT_H
