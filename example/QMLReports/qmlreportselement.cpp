#include "qmlreportselement.h"

QMLReportsElement::QMLReportsElement(QObject *parent) : QObject(parent)
{

}

void QMLReportsElement::reinit()
{
    /*if (m_center == "center"){
        m_htmlText = "<center>"+m_htmlText+"</center>";
    }*/

    //
    /*
     * voir comment centrer et justifier
     * améliorier la balise aligne
     * ajouter un composant QMLTable
     * ajouter propriété image dans logo et footer
     *
     */
}

QString QMLReportsElement::color() const
{
    return m_color;
}

void QMLReportsElement::setColor(const QString &a)
{

    if (a != m_color) {
        m_color = a;
        emit colorChanged();
    }
}

QString QMLReportsElement::family() const
{
    return m_family;
}

void QMLReportsElement::setFamily(const QString &a)
{

    if (a != m_family) {
        m_family = a;
        emit familyChanged();
    }
}

int QMLReportsElement::size() const
{
    return m_size;
}

void QMLReportsElement::setSize(const int &a)
{

    if (a != m_size) {
        m_size = a;
        emit sizeChanged();
    }
}

QString QMLReportsElement::style() const
{
    return m_style;
}

void QMLReportsElement::setStyle(const QString &a)
{

    if (a != m_style) {
        m_style = a;
        emit styleChanged();
    }
}

QString QMLReportsElement::weight() const
{
    return m_weight;
}

void QMLReportsElement::setWeight(const QString &a)
{

    if (a != m_weight) {
        m_weight = a;
        emit weightChanged();
    }
}

QString QMLReportsElement::decoration() const
{
    return m_decoration;
}

void QMLReportsElement::setDecoration(const QString &a)
{

    if (a != m_decoration) {
        m_decoration = a;
        emit decorationChanged();
    }
}


QString QMLReportsElement::htmlText() const
{
    return m_htmlText;
}

void QMLReportsElement::setHtmlText(const QString &a)
{
    if (a != m_htmlText) {
        m_htmlText = a;
        emit htmlTextChanged();
    }
}

qreal QMLReportsElement::xOffsetMM() const {return m_xOffsetMM;}
void QMLReportsElement::setXOffsetMM(const qreal &a) {m_xOffsetMM = a;}

qreal QMLReportsElement::yOffsetMM() const {return m_yOffsetMM;}
void QMLReportsElement::setYOffsetMM(const qreal &a) {m_yOffsetMM = a;}

QString QMLReportsElement::align() const {return m_align;}
void QMLReportsElement::setAlign(const QString &a)
{
   m_align = a;
}


