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
    m_nbPage = 1;
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

void QMLReportsReport::addLogo()
{
    QTextDocument tdLogo;
    QTextOption textOptionLogo;

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

    qreal xLogo, yLogo;
    xLogo = mm2px(m_logo->xOffsetMM());
    yLogo = mm2px(m_logo->yOffsetMM());
    m_lastY = yLogo + tdLogo.documentLayout()->documentSize().height();

    m_painter->save();
    m_painter->translate(xLogo, yLogo);
    tdLogo.drawContents(m_painter);
    m_painter->restore();

    m_logoHeight = yLogo + tdLogo.documentLayout()->documentSize().height();

}

void QMLReportsReport::addFooter()
{
    QTextDocument tdFooter;
    QTextOption textOptionFooter;

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

    m_painter->save();
    m_painter->translate(xFooter, yFooter);
    tdFooter.drawContents(m_painter);
    m_painter->restore();


    m_footerHeight = -mm2px(m_footer->yOffsetMM()) + tdFooter.documentLayout()->documentSize().height();
}

void QMLReportsReport::addConfidential()
{
    QTextDocument tdConfidential;
    QTextOption textOptionConfidential;
    textOptionConfidential.setAlignment(Qt::AlignHCenter);
    textOptionConfidential.setWrapMode(QTextOption::WordWrap);
    tdConfidential.setDefaultTextOption(textOptionConfidential);
    tdConfidential.setHtml("<div style='color:OrangeRed  ; font-family:georgia ; font-style:normal ; "
                           "font-size:300px ; font-weight:normal ; text-decoration:none '><pre>C  O  N  F  I  D  E  N  T  I  A  L</pre></div>");



    m_painter->save();
    m_painter->translate(30, m_writer->height()-175);
    m_painter->rotate(300);
    m_painter->setOpacity(0.5);
    tdConfidential.drawContents(m_painter);
    m_painter->restore();
}

void QMLReportsReport::addContent()
{
    QTextDocument tdContent;
    QTextOption textOptionContent;
    m_cursor = new QTextCursor(&tdContent);

    QString totalHtml;

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
        m_totalHtml += textHtmlContent;
    }

    m_cursor->insertHtml(m_totalHtml);

    while (!m_contentCompleted){
        checkPage();
    }

}

void QMLReportsReport::checkPage()
{
    int textLen = m_cursor->selectionEnd();
    int i = 0;

    QTextDocument *td = m_cursor->document();
    qreal xContent, yContent;
    xContent = 0;
    yContent = m_lastY;

    m_heightAvailable = m_writer->height() - m_logoHeight - m_footerHeight;
    m_heightNecessary = td->documentLayout()->documentSize().height();

    qDebug() << "Page n°" << m_nbPage;
    qDebug() << m_heightNecessary << "/" << m_heightAvailable;
    qDebug() << m_writer->height();
    qDebug() << "Logo Height :" << m_logoHeight << " -  " << "Footer Height :" << m_footerHeight;
    qDebug() << "===========";


    if (m_heightNecessary > m_heightAvailable){
        m_cursor->movePosition(QTextCursor::Start);
        qDebug() << m_cursor->selectionEnd();

        while (i < textLen){
            m_cursor->movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
            QString newHtml = m_cursor->selection().toHtml();

            QTextDocument doc;
            QTextCursor cursor(&doc);
            cursor.insertHtml(newHtml);
            qreal height = doc.documentLayout()->documentSize().height();
            if (height >= m_heightAvailable) break;
            i = cursor.selectionEnd();
        }

        m_cursor->setPosition(i-1);
        m_cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        QString htmlToo = m_cursor->selection().toHtml();

        m_cursor->setPosition(i-1);
        m_cursor->movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
        QString htmlToPrint = m_cursor->selection().toHtml();

        m_cursor->select(QTextCursor::Document);
        m_cursor->removeSelectedText();
        m_cursor->insertHtml(htmlToPrint);

        m_painter->save();
        m_painter->translate(xContent, yContent);
        td->drawContents(m_painter);
        m_painter->restore();

        m_writer->newPage();
        m_nbPage += 1;
        m_lastY = 0;
        addLogo();
        addFooter();
        addConfidential();

        m_cursor->select(QTextCursor::Document);
        m_cursor->removeSelectedText();
        m_cursor->insertHtml(htmlToo);
    }
    else {
        m_painter->translate(xContent, yContent);
        td->drawContents(m_painter);
        m_contentCompleted = true;
    }

}

void QMLReportsReport::print()
{
    m_painter = new QPainter(m_writer);

    addLogo();
    addFooter();
    addConfidential();
    addContent();


    if (m_painter->end()){
        QDesktopServices::openUrl(QUrl("file:"+m_fileName));
    }
}
