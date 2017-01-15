#ifndef QMLREPORTSCONFIDENTIAL_H
#define QMLREPORTSCONFIDENTIAL_H

#include <QObject>

#include "qmlreportselement.h"


class QMLReportsConfidential : public QMLReportsElement
{
    Q_OBJECT
public:
    explicit QMLReportsConfidential();

public slots:
    void inti();

};

#endif // QMLREPORTSCONFIDENTIAL_H
