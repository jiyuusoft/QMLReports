#include "qmlreports.h"


QMLReports::QMLReports(QObject *parent)
{
    connect(this, SIGNAL(fileNameChanged()), this, SLOT(init()));
}

void QMLReports::import ()
{
    qmlRegisterType<QMLReports>("QMLReports", 1, 0, "Report");
    qmlRegisterType<QMLReportsContent>("QMLReports", 1, 0, "ReportContent");
    qmlRegisterType<QMLReportsFooter>("QMLReports", 1, 0, "ReportFooter");
    qmlRegisterType<QMLReportsHeader>("QMLReports", 1, 0, "ReportHeader");
}

void QMLReports::init()
{
    m_writer = new QPdfWriter(m_fileName);
    m_writer->setResolution(m_resolution);
    QPageSize pageSize(QPageSize::A4);
    QMarginsF margins(m_margins, m_margins, m_margins, m_margins);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, margins, QPageLayout::Millimeter);
    m_writer->setPageLayout(pageLayout);
    m_nbPage = 1;
}

QString QMLReports::fileName() const
{
    return m_fileName;
}

void QMLReports::setFileName(const QString &fileName)
{
    if (fileName != m_fileName) {
        m_fileName = fileName;
        emit fileNameChanged();
    }
}

int QMLReports::resolution() const {return m_resolution;}
void QMLReports::setResolution(const int &resolution) {m_resolution = resolution;}

qreal QMLReports::margins() const {return m_margins;}
void QMLReports::setMargins(const qreal &margins) {m_margins = margins;}



QMLReportsHeader *QMLReports::header() const
{
    return m_header;
}

void QMLReports::setHeader(QMLReportsHeader *header)
{
    m_header = header;
}

QMLReportsFooter *QMLReports::footer() const
{
    return m_footer;
}

void QMLReports::setFooter(QMLReportsFooter *footer)
{
    m_footer = footer;
}

QQmlListProperty<QMLReportsContent> QMLReports::contents()
{
    return QQmlListProperty<QMLReportsContent>(this, m_contents);
}

int QMLReports::contentsCount() const
{
    return m_contents.count();
}

QMLReportsContent *QMLReports::content(int index) const
{
    return m_contents.at(index);
}

QString QMLReports::setFormat(QMLReportsElement *element)
{
    QString styleBeginContent = tr("<div style='color:%1 ; font-family:%2 ; font-style:%3 ; "
                                   "font-size:%4px ; font-weight:%5 ; text-decoration:%6 ; ' align=%7>"
                                   "").arg(element->color(),
                                           element->family(),
                                           element->style(),
                                           QString::number(m_resolution / element->size()),  // il faut rendre inversement proportionel cette valeur
                                           element->weight(),
                                           element->decoration(),
                                           element->align());

    QString styleEndContent = "</div>";
    QString textHtmlContent = styleBeginContent + element->htmlText() + styleEndContent;

    return textHtmlContent;

}

void QMLReports::addHeader()
{
    QTextDocument tdLogo;
    QTextOption textOptionLogo;

    m_header->reinit();
    textOptionLogo.setWrapMode(QTextOption::WordWrap);
    tdLogo.setDefaultTextOption(textOptionLogo);
    tdLogo.setTextWidth(m_writer->width());
    tdLogo.setHtml(setFormat(m_header));

    qreal xLogo, yLogo;
    xLogo = mm2px(m_header->xOffsetMM());
    yLogo = mm2px(m_header->yOffsetMM());
    m_lastY = yLogo + tdLogo.documentLayout()->documentSize().height();

    m_painter->save();
    m_painter->translate(xLogo, yLogo);
    tdLogo.drawContents(m_painter);
    m_painter->restore();

    m_logoHeight = yLogo + tdLogo.documentLayout()->documentSize().height();

}

void QMLReports::addFooter()
{
    QTextDocument tdFooter;
    QTextOption textOptionFooter;

    m_footer->reinit();
    textOptionFooter.setWrapMode(QTextOption::WordWrap);
    tdFooter.setDefaultTextOption(textOptionFooter);
    tdFooter.setTextWidth(m_writer->width());
    tdFooter.setHtml(setFormat(m_footer));

    qreal xFooter, yFooter;
    xFooter = mm2px(m_footer->xOffsetMM());
    yFooter = m_writer->height() + mm2px(m_footer->yOffsetMM()) - tdFooter.documentLayout()->documentSize().height();

    m_painter->save();
    m_painter->translate(xFooter, yFooter);
    tdFooter.drawContents(m_painter);
    m_painter->restore();

    m_footerHeight = -mm2px(m_footer->yOffsetMM()) + tdFooter.documentLayout()->documentSize().height();
}

void QMLReports::addConfidential()
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

void QMLReports::addContent()
{
    QTextDocument tdContent;
    QTextOption textOptionContent;
    m_cursor = new QTextCursor(&tdContent);

    for (int i=0; i < m_contents.length(); i++){
        QMLReportsContent *content = m_contents.at(i);
        content->reinit();

        textOptionContent.setWrapMode(QTextOption::WordWrap);
        tdContent.setDefaultTextOption(textOptionContent);
        tdContent.setTextWidth(m_writer->width());
        m_totalHtml += setFormat(content);
    }

    m_cursor->insertHtml(m_totalHtml);

    while (!m_contentCompleted){
        checkPage();
    }

}

void QMLReports::checkPage()
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
        addHeader();
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

void QMLReports::print()
{
    m_painter = new QPainter(m_writer);

    addHeader();
    addFooter();
    addConfidential();
    addContent();


    if (m_painter->end()){
        QTime chrono;
        chrono.start();
        while( chrono.elapsed() < 500 ){   }

        QDesktopServices::openUrl(QUrl("file:"+m_fileName));
    }
}
