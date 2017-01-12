#include "qmlreportsreport.h"

QMLReportsReport::QMLReportsReport(QObject *parent)
{
    connect(this, SIGNAL(fileNameChanged()), this, SLOT(init()));
}

void QMLReportsReport::init()
{

    m_writer = new QPdfWriter(m_fileName);
    m_writer->setResolution(m_resolution);
    QPageSize pageSize(QPageSize::A4);
    QMarginsF margins(m_margins, m_margins, m_margins, m_margins);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, margins, QPageLayout::Millimeter);
    m_writer->setPageLayout(pageLayout);


    m_rectContent = new QRectF(0, 0, m_writer->width(), m_writer->height());
    //m_heightContentAvailable = m_writer->height();
}

QString QMLReportsReport::fileName() const
{
    return m_fileName;
}

void QMLReportsReport::setFileName(const QString &fileName)
{
    if (fileName != m_fileName) {
        m_fileName = fileName;
        emit fileNameChanged();
    }
}

int QMLReportsReport::resolution() const {return m_resolution;}
void QMLReportsReport::setResolution(const int &resolution) {m_resolution = resolution;}

qreal QMLReportsReport::margins() const {return m_margins;}
void QMLReportsReport::setMargins(const qreal &margins) {m_margins = margins;}



QMLReportsLogo *QMLReportsReport::logo() const
{
    return m_logo;
}

void QMLReportsReport::setLogo(QMLReportsLogo *logo)
{
    m_logo = logo;
}

QMLReportsFooter *QMLReportsReport::footer() const
{
    return m_footer;
}

void QMLReportsReport::setFooter(QMLReportsFooter *footer)
{
    m_footer = footer;
}

QQmlListProperty<QMLReportsContent> QMLReportsReport::contents()
{
    return QQmlListProperty<QMLReportsContent>(this, m_contents);
}

int QMLReportsReport::contentsCount() const
{
    return m_contents.count();
}

QMLReportsContent *QMLReportsReport::content(int index) const
{
    return m_contents.at(index);
}


void QMLReportsReport::print()
{
    m_painter = new QPainter(m_writer);

    QTextDocument tdLogo;
    QTextDocument tdFooter;
    QTextDocument tdContent;
    QTextOption textOptionLogo;
    QTextOption textOptionFooter;
    QTextOption textOptionContent;
    qreal lastY;



    /* Add an logo to PDF File */
    if (m_logo->align() == "center"){
        textOptionLogo.setAlignment(Qt::AlignHCenter);
    }
    else{
        textOptionLogo.setAlignment(Qt::AlignJustify);
    }
    textOptionLogo.setWrapMode(QTextOption::WordWrap);
    tdLogo.setDefaultTextOption(textOptionLogo);

    QString styleBeginLogo = tr("<div style='color:%1 ; font-family:%2 ; font-style:%3 ; "
                                "font-size:%4px ; font-weight:%5 ; text-decoration:%6'>"
                                "").arg(m_logo->color(),
                                        m_logo->family(),
                                        m_logo->style(),
                                        QString::number(m_logo->size()),
                                        m_logo->weight(),
                                        m_logo->decoration());
    QString styleEndLogo = "</div>";
    QString textHtmlLogo = styleBeginLogo + m_logo->htmlText() + styleEndLogo;
    tdLogo.setTextWidth(m_writer->width());
    tdLogo.setHtml(textHtmlLogo);

    //m_xLogoOffset = xOffsetMM;
    //m_yLogoOffset = yOffsetMM;
    //m_logoTotalHeight = tdLogo.documentLayout()->documentSize().height() + mm2px(yOffsetMM);

    qreal xLogo, yLogo;
    xLogo = mm2px(m_logo->xOffsetMM());
    yLogo = mm2px(m_logo->yOffsetMM());
    lastY = yLogo + tdLogo.documentLayout()->documentSize().height();

    m_painter->translate(xLogo, yLogo);
    tdLogo.drawContents(m_painter);
    m_painter->translate(-xLogo, -yLogo);

    //m_totalHeightDoc += td.documentLayout()->documentSize().height() + mm2px(yOffsetMM);
    //m_totalHeightDoc += m_logo->documentLayout()->documentSize().height() + mm2px(yOffsetMM);


    //m_heightContentAvailable -=  m_logo->documentLayout()->documentSize().height() + mm2px(yOffsetMM);
    //m_heightContentAvailable -=  td.documentLayout()->documentSize().height() + mm2px(yOffsetMM);

    //m_rectContent->setHeight(m_heightContentAvailable);



    //=======================================//

    /* Add a Footer to PDF File */

    if (m_footer->align() == "center"){
        textOptionFooter.setAlignment(Qt::AlignHCenter);
    }
    else{
        textOptionFooter.setAlignment(Qt::AlignJustify);
    }
    textOptionFooter.setWrapMode(QTextOption::WordWrap);
    tdFooter.setDefaultTextOption(textOptionFooter);

    QString styleBeginFooter = tr("<div style='color:%1 ; font-family:%2 ; font-style:%3 ; "
                                  "font-size:%4px ; font-weight:%5 ; text-decoration:%6'>"
                                  "").arg(m_footer->color(),
                                          m_footer->family(),
                                          m_footer->style(),
                                          QString::number(m_footer->size()),
                                          m_footer->weight(),
                                          m_footer->decoration());


    QString styleEndFooter = "</div>";
    QString textHtmlFooter = styleBeginFooter + m_footer->htmlText() + styleEndFooter;
    tdFooter.setTextWidth(m_writer->width());
    tdFooter.setHtml(textHtmlFooter);

    qreal xFooter, yFooter;
    xFooter = mm2px(m_footer->xOffsetMM());
    yFooter = m_writer->height() + mm2px(m_footer->yOffsetMM()) - tdFooter.documentLayout()->documentSize().height();

    m_painter->translate(xFooter, yFooter);
    tdFooter.drawContents(m_painter);
    m_painter->translate(-xFooter, -yFooter);


    //=======================================//

    /* Add Contents to PDF File */

    qDebug() << "lastY" << lastY;
    qDebug() << "height logo" << tdLogo.documentLayout()->documentSize().height();

    for (int i=0; i < m_contents.length(); i++){
        QMLReportsContent *content = m_contents.at(i);
        if (content->align() == "center"){
            textOptionContent.setAlignment(Qt::AlignHCenter);
        }
        else{
            textOptionContent.setAlignment(Qt::AlignJustify);
        }

        textOptionContent.setWrapMode(QTextOption::WordWrap);
        tdContent.setDefaultTextOption(textOptionContent);
        tdContent.setTextWidth(m_writer->width());

        QString styleBeginContent = tr("<div style='color:%1 ; font-family:%2 ; font-style:%3 ; "
                                       "font-size:%4px ; font-weight:%5 ; text-decoration:%6'>"
                                       "").arg(content->color(),
                                               content->family(),
                                               content->style(),
                                               QString::number(content->size()),
                                               content->weight(),
                                               content->decoration());

        QString styleEndContent = "</div>";
        QString textHtmlContent = styleBeginContent + content->htmlText() + styleEndContent;
        tdContent.setHtml(textHtmlContent);

        qreal xContent, yContent;
        xContent = mm2px(content->xOffsetMM());
        yContent = lastY + mm2px(content->yOffsetMM());
        m_painter->translate(xContent, yContent);
        tdContent.drawContents(m_painter);
        m_painter->translate(-xContent, -yContent);
        lastY += tdContent.documentLayout()->documentSize().height();

        //qDebug() << textHtmlContent;
        //qDebug() <<"x:" << xContent << " -  y:" << yContent << " -  height:" << tdContent.documentLayout()->documentSize().height();
        //qDebug() << lastY;
        //qDebug() << "    ";
    }


    if (m_painter->end()){
        QDesktopServices::openUrl(QUrl("file:"+m_fileName));
    }
}
