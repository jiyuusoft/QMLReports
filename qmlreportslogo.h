#ifndef QMLREPORTSLOGO_H
#define QMLREPORTSLOGO_H

#include <QObject>
#include <QTextDocument>
#include <QTextOption>


class QMLReportsLogo : public QTextDocument
{
    Q_OBJECT
public:
    explicit QMLReportsLogo(QString htmlLogo=Q_NULLPTR, QTextOption::WrapMode wrapMode = QTextOption::WordWrap, QObject *parent=Q_NULLPTR);

public slots:
    void setLogo(QString htmlLogo, QTextOption::WrapMode wrapMode=QTextOption::WordWrap);
};

#endif // QMLREPORTSLOGO_H
