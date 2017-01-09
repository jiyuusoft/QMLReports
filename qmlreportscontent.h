#ifndef QMLREPORTSCONTENT_H
#define QMLREPORTSCONTENT_H

#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextOption>

class QMLReportsContent : public QTextDocument
{
    Q_OBJECT
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)
    Q_PROPERTY(QString size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QString weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(QString decoration READ decoration WRITE setDecoration NOTIFY decorationChanged)
    Q_PROPERTY(QString htmlText READ htmlText WRITE setHtmlText NOTIFY htmlTextChanged)


public:
    //explicit QMLReportsContent(QString htmlText="", QTextOption::WrapMode wrapMode = QTextOption::WordWrap, QObject *parent = Q_NULLPTR);
    explicit QMLReportsContent(QString htmlText="", QObject *parent = Q_NULLPTR);

    QString color() const;
    void setColor(const QString &a);

    QString family() const;
    void setFamily(const QString &a);

    QString size() const;
    void setSize(const QString &a);

    QString style() const;
    void setStyle(const QString &a);

    QString weight() const;
    void setWeight(const QString &a);

    QString decoration() const;
    void setDecoration(const QString &a);

    QString htmlText() const;
    void setHtmlText(const QString &a);


public slots:
    void setHtmlContent(QString html, QTextOption::WrapMode wrapMode=QTextOption::WordWrap);


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
    QString m_size = "30";
    QString m_style = "normal";
    QString m_weight = "normal";
    QString m_decoration = "none";
    QString m_htmlText;
};


#endif // QMLREPORTSCONTENT_H
