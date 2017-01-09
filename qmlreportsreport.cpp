#include "qmlreportsreport.h"

//QMLReportsReport::QMLReportsReport(QString fileName, qreal margin, qreal resolution, QObject *parent)
QMLReportsReport::QMLReportsReport(QString fileName, QObject *parent)
{
    /*    IDEES
     *    - inclure les logos et footer dans les marges ?
     *
     */

    this->connect(this, SIGNAL(fileNameChanged()), this, SLOT(init()));
    qreal margin = 10;
    qreal resolution = 300;
    QString fileName2 = "/Users/charlie/test.pdf";

    this->m_writer = new QPdfWriter(fileName2);
    this->setResolution(resolution);
    this->m_margin = margin;
    QPageSize pageSize(QPageSize::A4);
    QMarginsF margins(margin, margin, margin, margin);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, margins, QPageLayout::Millimeter);
    this->m_writer->setPageLayout(pageLayout);

    //m_rectContent = new QRectF(0, 0, m_writer->width(), m_writer->height());
    //m_heightContentAvailable = m_writer->height();


    if (this->begin(this->m_writer)){
        qDebug () << "Ca fonctionne";
    }
     else{qDebug() << "Painter rencontre un souci" ;}

}

void QMLReportsReport::init()
{
    qDebug() << "toto";
    /*
     * mettre ici le code pour initialiser le painter
     *
     */
}

QString QMLReportsReport::fileName() const
{

    //this->begin(this->m_writer);
    return m_fileName;
}

void QMLReportsReport::setFileName(const QString &a)
{

    if (a != m_fileName) {
        m_fileName = a;
        emit fileNameChanged();
    }
}
/*
QTextDocument QMLReportsReport::content() const
{
    return m_qmlContent;
}

void QMLReportsReport::setContent(const QTextDocument &a)
{

    if (a != m_qmlContent) {
        m_qmlContent = a;
        emit contentChanged();
    }
}
*/


/*
QObject *QMLReportsReport::logo()
{
    return m_qmlLogo;
}

void QMLReportsReport::setLogo(QObject &a)
{
    if (&a != m_qmlLogo) {
        m_qmlLogo = &a;
        emit logoChanged();
    }
}
*/



qreal QMLReportsReport::widthMM()
{
    return this->m_writer->widthMM();
}

void QMLReportsReport::setResolution(qreal resolution)
{
    this->m_writer->setResolution(resolution);
}


void QMLReportsReport::addPage()
{
    qDebug() << "Create a new page";
    m_nbPage += 1;
    m_heightContentAvailable = m_writer->height();

    this->save();
    this->m_writer->newPage();
    this->translate(0, -m_totalHeightDoc);
    m_totalHeightDoc = 0;
    this->restore();

    this->addLogo(m_logo, m_xLogoOffset, m_yLogoOffset);
    this->addFooter(m_footer, m_xFooterOffset, m_yFooterOffset);

    /*prévoir :
     *   - mise en place de l'header automatiquement
     *   - repartir au début de la page
     *   - contrôle automatique
     *   - mise en place du footer automatiquement
     */
}

void QMLReportsReport::addLogo(QMLReportsLogo *logo, qreal xOffsetMM, qreal yOffsetMM)
{
    /* Merorize the xOffset ant yOffset, Add a logo to Document and return to X origine */
    m_logo = logo;
    m_xLogoOffset = xOffsetMM;
    m_yLogoOffset = yOffsetMM;
    m_logoTotalHeight = m_logo->documentLayout()->documentSize().height() + mm2px(yOffsetMM);

    qreal x, y;
    x = mm2px(xOffsetMM);
    y = m_totalHeightDoc + mm2px(yOffsetMM);

    this->translate(x, y);
    m_logo->drawContents(this);
    m_totalHeightDoc += m_logo->documentLayout()->documentSize().height() + mm2px(yOffsetMM);
    this->translate(-x, -y);

    m_heightContentAvailable -=  m_logo->documentLayout()->documentSize().height() + mm2px(yOffsetMM);
    m_rectContent->setHeight(m_heightContentAvailable);
}

void QMLReportsReport::addFooter(QMLReportsFooter *footer, qreal xOffsetMM, qreal yOffsetMM)
{
    /* Add a HTML footer to Document and return to X origine */
    m_footer = footer;
    m_xFooterOffset = xOffsetMM;
    m_yFooterOffset = yOffsetMM;

    qreal x, y;
    x = mm2px(xOffsetMM);
    y = m_writer->height() - m_footer->documentLayout()->documentSize().height()+mm2px(yOffsetMM);

    this->translate(x, y);
    m_footer->setTextWidth(m_writer->width()-mm2px(xOffsetMM));
    m_footer->drawContents(this);
    this->translate(-x, -y);

    m_heightContentAvailable -=  m_footer->documentLayout()->documentSize().height() + mm2px(yOffsetMM);
    m_rectContent->setHeight(m_heightContentAvailable);
}

void QMLReportsReport::addContent(QMLReportsContent *content, qreal xOffsetMM, qreal yOffsetMM)
{
    /* Add a HTML content to Document and return to X origine */
    m_content = content;
    m_content->setTextWidth(m_writer->width()-mm2px(xOffsetMM));
    m_totalContent += m_content->documentLayout()->documentSize().height() + mm2px(yOffsetMM);

    qreal x, y;
    x = mm2px(xOffsetMM);
    y = m_totalHeightDoc + mm2px(yOffsetMM);

    m_totalHeightDoc += m_content->documentLayout()->documentSize().height()+mm2px(yOffsetMM);

    if (m_totalContent > m_nbPage * m_rectContent->height()) {
        addPage();
        this->translate(0, m_logoTotalHeight);
        m_content->drawContents(this);
        this->translate(-x, -y);
    }
    else {
        this->translate(x, y);
        m_content->drawContents(this);
        this->translate(-x, -y);
    }

}



