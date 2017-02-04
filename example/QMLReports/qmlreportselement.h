#ifndef QMLREPORTSELEMENT_H
#define QMLREPORTSELEMENT_H

#include <QObject>
#include <QDebug>

class QMLReportsElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QString weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(QString decoration READ decoration WRITE setDecoration NOTIFY decorationChanged)
    Q_PROPERTY(QString htmlText READ htmlText WRITE setHtmlText NOTIFY htmlTextChanged)
    Q_PROPERTY(qreal xOffsetMM READ xOffsetMM WRITE setXOffsetMM)
    Q_PROPERTY(qreal yOffsetMM READ yOffsetMM WRITE setYOffsetMM)
    Q_PROPERTY(QString align READ align WRITE setAlign)

public:
    explicit QMLReportsElement(QObject *parent=Q_NULLPTR);

    QString color() const;
    void setColor(const QString &a);

    QString family() const;
    void setFamily(const QString &a);

    int size() const;
    void setSize(const int &a);

    QString style() const;
    void setStyle(const QString &a);

    QString weight() const;
    void setWeight(const QString &a);

    QString decoration() const;
    void setDecoration(const QString &a);

    QString htmlText() const;
    void setHtmlText(const QString &a);

    qreal xOffsetMM() const;
    void setXOffsetMM(const qreal &a);

    qreal yOffsetMM() const;
    void setYOffsetMM(const qreal &a);

    QString align() const;
    void setAlign(const QString &a);

public slots:
    void reinit();

signals:
    void colorChanged();
    void familyChanged();
    void sizeChanged();
    void styleChanged();
    void weightChanged();
    void decorationChanged();
    void htmlTextChanged();

private:
    QString m_color = "black";
    QString m_family = "verdana";
    int m_size = 30;
    QString m_style = "normal";
    QString m_weight = "normal";
    QString m_decoration = "none";
    QString m_htmlText;
    qreal m_xOffsetMM;
    qreal m_yOffsetMM;
    QString m_align = "left";


};

#endif // QMLREPORTSELEMENT_H
