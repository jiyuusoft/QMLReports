#include "qmlreports.h"


QMLReports::QMLReports(QObject *parent){ }

void QMLReports::import ()
{
    qmlRegisterType<QMLReports>("QMLReports", 1, 0, "Report");
    qmlRegisterType<QMLReportsContent>("QMLReports", 1, 0, "ReportContent");
    qmlRegisterType<QMLReportsFooter>("QMLReports", 1, 0, "ReportFooter");
    qmlRegisterType<QMLReportsHeader>("QMLReports", 1, 0, "ReportHeader");
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
    qreal k=1;
    qreal kReso =1;
    QString styleBeginContent = tr("<div style='color:%1 ; font-family:%2 ; font-style:%3 ; "
                                   "font-size:%4px ; font-weight:%5 ; text-decoration:%6 ; ' align=%7>"
                                   "").arg(element->color(),
                                           element->family(),
                                           element->style(),
                                           QString::number(element->size() * k * kReso),  // il faut rendre inversement proportionel cette valeur
                                           element->weight(),
                                           element->decoration(),
                                           element->align());

    QString styleEndContent = "</div>";
    QString textHtmlContent = styleBeginContent + element->htmlText() + styleEndContent;

    return textHtmlContent;

}

void QMLReports::newPage()
{
    m_writer->newPage();
    m_nbPage += 1;
    m_lastY = 0;
    addHeader();
    addFooter();
    addConfidential();
    m_painter->setPen(Qt::green);
    m_painter->drawRect(m_rectContent);

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
    QRectF rect(xLogo, yLogo, m_writer->width(), tdLogo.documentLayout()->documentSize().height());
    m_painter->setPen(Qt::red);
    m_painter->drawRect(rect);

    m_logoHeight = yLogo + tdLogo.documentLayout()->documentSize().height();
    m_beginContentY = m_logoHeight;
    m_heightAvailable -= m_logoHeight;
    m_rectContent.setTop(m_beginContentY);
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
    QRectF rect(xFooter, yFooter, m_writer->width(), tdFooter.documentLayout()->documentSize().height());
    m_painter->setPen(Qt::red);
    m_painter->drawRect(rect);

    m_footerHeight = -mm2px(m_footer->yOffsetMM()) + tdFooter.documentLayout()->documentSize().height();
    m_endContentY = m_writer->height() - m_footerHeight;
    m_heightAvailable -= m_footerHeight;
    m_rectContent.setBottom(m_endContentY-mm2px(4));

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
    m_painter->setPen(Qt::green);
    m_painter->drawRect(m_rectContent);

    for (int i=0; i < m_contents.length(); i++){
        QMLReportsContent *content = m_contents.at(i);
        m_totalHtml += setFormat(content);
    }

    QTextDocument tdContent;
    QTextOption textOptionContent;
    textOptionContent.setWrapMode(QTextOption::WordWrap);
    tdContent.setDefaultTextOption(textOptionContent);
    tdContent.setTextWidth(m_writer->width());

    setContent(&tdContent);
}

void QMLReports::setContent(QTextDocument *doc, int beginPosition)
{
    doc->clear();
    QString htmlText;
    m_cursor = new QTextCursor(doc);
    m_cursor->insertHtml(m_totalHtml);

    int lenTextToPrint = m_cursor->selectionEnd()-beginPosition;

    qDebug() << "   ";
    qDebug() << "============";
    qDebug() << "Page n°" << m_nbPage;
    qDebug() << "Initial text lenght" << m_cursor->selectionEnd();
    qDebug() << "Begin position" << beginPosition;
    qDebug() << "Text to print" << lenTextToPrint;

    //How do if the first line is empty (eg: <br>,...) ??.

    if (beginPosition != 0)
    {
        m_cursor->setPosition(beginPosition);
        m_cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        htmlText = m_cursor->selection().toHtml();
        m_cursor->select(QTextCursor::Document);
        m_cursor->removeSelectedText();
        m_cursor->insertHtml(htmlText);
    }
    else {
        htmlText = m_totalHtml;
    }

    qDebug() << "Current TextDoc height" << doc->documentLayout()->documentSize().height();
    qDebug() << "Available per page" << m_rectContent.height();

    int actPosi = 0;
    if (doc->documentLayout()->documentSize().height() > m_rectContent.height()){
        doc->clear();
        while(doc->documentLayout()->documentSize().height() < m_rectContent.height())
        {
            QTextCursor *cursor = new QTextCursor(doc);
            cursor->insertHtml(htmlText);
            cursor->setPosition(actPosi);
            cursor->movePosition(QTextCursor::Down);

            actPosi = cursor->position();
            cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
            cursor->removeSelectedText();
        }
        paintContent(doc);

        m_alreadyPaint += actPosi;
        qDebug() << "Last Position" << actPosi;
        qDebug() << "Already print" << m_alreadyPaint;
        if (actPosi < lenTextToPrint){
            newPage();
            setContent(doc, m_alreadyPaint);
        }
    }
    else {
        paintContent(doc);
    }
}

void QMLReports::paintContent(QTextDocument *doc)
{
    m_painter->save();
    m_painter->translate(m_rectContent.topLeft());
    doc->drawContents(m_painter);
    m_painter->restore();
}

void QMLReports::print()
{
    m_writer = new QPdfWriter(m_fileName);
    m_writer->setResolution(m_resolution);
    QPageSize pageSize(QPageSize::A4);
    QMarginsF margins(m_margins, m_margins, m_margins, m_margins);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, margins, QPageLayout::Millimeter);
    m_writer->setPageLayout(pageLayout);
    m_nbPage = 1;
    m_heightAvailable = m_writer->height();
    m_rectContent.setCoords(0, 0, m_writer->width(), 0);
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
        m_contentCompleted = false;
        m_totalHtml = "";
        m_alreadyPaint = 0;
    }
}
