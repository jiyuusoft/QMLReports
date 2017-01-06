#ifndef QMLREPORTSFOOTER_H
#define QMLREPORTSFOOTER_H

#include <QObject>
#include <QTextDocument>
#include <QTextOption>


class QMLReportsFooter : public QTextDocument
{
    Q_OBJECT
public:
    explicit QMLReportsFooter(QString htmlFooter = Q_NULLPTR, QTextOption::WrapMode wrapMode = QTextOption::WordWrap, QObject *parent = Q_NULLPTR);

private slots:

public slots:

};

#endif // QMLREPORTSFOOTER_H
