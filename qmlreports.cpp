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
    qreal kReso = 1;
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
    //m_painter->setPen(Qt::green);
    //m_painter->drawRect(m_rectContent);

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

    /*
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
    */
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

    /*
    qreal xFooter, yFooter;
    xFooter = mm2px(m_footer->xOffsetMM());
    yFooter = m_writer->height() + mm2px(m_footer->yOffsetMM()) - tdFooter.documentLayout()->documentSize().height();
    */
    /*
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
    m_rectContent.setBottom(m_endContentY-mm2px(2));
    */

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

    /*
    m_painter->save();
    m_painter->translate(30, m_writer->height()-175);
    m_painter->rotate(300);
    m_painter->setOpacity(0.5);
    tdConfidential.drawContents(m_painter);
    m_painter->restore();
    */
}

void QMLReports::addContent()
{
    //m_painter->setPen(Qt::green);
    //m_painter->drawRect(m_rectContent);

    for (int i=0; i < m_contents.length(); i++){
        QMLReportsContent *content = m_contents.at(i);
        m_totalHtml += setFormat(content);
    }

    /*
    QTextDocument tdContent;
    QTextOption textOptionContent;
    textOptionContent.setAlignment(Qt::AlignJustify);
    textOptionContent.setWrapMode(QTextOption::WordWrap);
    tdContent.setDefaultTextOption(textOptionContent);
    tdContent.setTextWidth(m_writer->width());
    tdContent.setPageSize(QSizeF(m_writer->width(), m_rectContent.height()));
    tdContent.setHtml(m_totalHtml);


    m_painter->save();
    m_painter->translate(m_rectContent.topLeft());
    tdContent.drawContents(m_painter);
    m_painter->restore();
*/
    //setContent(&tdContent);

}

void QMLReports::setContent(QTextDocument *doc, int beginPosition)
{
    /*
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
        m_cursor->setPosition(beginPosition-1);
        //m_cursor->movePosition(QTextCursor::PreviousWord);
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
    */
}

void QMLReports::paintContent(QTextDocument *doc)
{
    /*
    m_painter->save();
    m_painter->translate(m_rectContent.topLeft());
    doc->drawContents(m_painter);
    m_painter->restore();
    */
}

void QMLReports::print()
{
    /*
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
*/

    //addHeader();
    //addFooter();
    //addConfidential();
    //m_painter->end();
    //addContent();

    /*
    QTextDocument doc;
    QTextCursor cursor(&doc);
    cursor.insertHtml(m_totalHtml);
    //doc.drawContents(m_painter);
    doc.setPageSize(QSizeF(m_writer->width(), m_writer->height())); // This is necessary if you want to hide the page number
    doc.print(m_writer);
    */
    //m_painter->end();
    //QDesktopServices::openUrl(QUrl("file:"+m_fileName));


    /*
    if (m_painter->end()){
        QTime chrono;
        chrono.start();
        while( chrono.elapsed() < 500 ){   }

        QDesktopServices::openUrl(QUrl("file:"+m_fileName));

    }
    */


    //QPrinter printer(QPrinter::PrinterResolution);
    //printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setPaperSize(QPrinter::A4);
    //printer.setOutputFileName("/Users/charlie/toto.pdf");

    /*
    QPdfWriter *writer = new QPdfWriter("/Users/charlie/toto.pdf");
    writer->setResolution(m_resolution);
    QPageSize pageSize2(QPageSize::A4);
    QMarginsF margins2(m_margins, m_margins, m_margins, m_margins);
    QPageLayout pageLayout2(pageSize2, QPageLayout::Portrait, margins2, QPageLayout::Millimeter);
    writer->setPageLayout(pageLayout2);

    QTextDocument doc;
    doc.setHtml(m_totalHtml);
    //doc.drawContents(m_painter);
    doc.setPageSize(QSizeF(m_writer->width(), m_writer->height())); // This is necessary if you want to hide the page number
    doc.print(writer);

    //QDesktopServices::openUrl(QUrl("file:"+m_fileName));
    QDesktopServices::openUrl(QUrl("file:/Users/charlie/toto.pdf"));
    */

    m_contentCompleted = false;
    m_totalHtml = "";
    m_alreadyPaint = 0;

    test();


}

void QMLReports::test()
{
    m_writer = new QPdfWriter(m_fileName);
    m_writer->setResolution(m_resolution);
    QPageSize pageSize(QPageSize::A4);
    QMarginsF margins(m_margins, m_margins, m_margins, m_margins);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, margins, QPageLayout::Millimeter);
    m_writer->setPageLayout(pageLayout);
    QRectF rectPrinter;
    rectPrinter.setCoords(0, 0, m_writer->width(), m_writer->height());


    ///Limiter la taille de Header & Footer.


    ///Setting up the header and calculating the header size
    QTextDocument *tdHeader = new QTextDocument(this);
    tdHeader->setPageSize(rectPrinter.size());
    tdHeader->setHtml(setFormat(m_header));
    QSizeF headerSize = tdHeader->size();

    ///Setting up the footer and calculating the footer size
    QTextDocument *tdFooter = new QTextDocument(this);
    tdFooter->setPageSize(rectPrinter.size());
    tdFooter->setHtml(setFormat(m_footer));
    QSizeF footerSize = tdFooter->size();

    ///Setting up the footer and calculating the footer size
    QTextDocument *tdConfidential = new QTextDocument(this);
    tdConfidential->setPageSize(rectPrinter.size());
    tdConfidential->setHtml("<div style='color:OrangeRed  ; font-family:georgia ; font-style:normal ; "
                            "font-size:100px ; font-weight:normal ; text-decoration:none '><pre>C  O  N  F  I  D  E  N  T  I  A  L</pre></div>");
    //QSizeF confidentialSize = tdConfidential->size();

    ///Calculating the main document size for one page
    QSizeF contentSize(rectPrinter.width(), (rectPrinter.height() - headerSize.toSize().height() - footerSize.toSize().height()));

    ///Setting up the center page
    QTextDocument *tdContent = new QTextDocument(this);
    addContent();
    tdContent->setHtml(m_totalHtml);
    tdContent->setPageSize(contentSize);

    ///Setting up the rectangles for each section.
    QRectF headerRect = QRectF(QPoint(0,0), tdHeader->size().toSize());
    QRectF footerRect = QRectF(QPoint(0,0), tdFooter->size().toSize());
    QRectF confidentialRect = QRectF(QPoint(0,0), tdConfidential->size().toSize());
    QRectF contentRect = QRectF(QPoint(0,0), tdContent->size().toSize());    /// Main content rectangle.
    QRectF currentRect = QRectF(QPoint(0,0), contentSize.toSize());        /// Current main content rectangle.

    QPainter painter(m_writer);
    painter.save();

    while (currentRect.intersects(contentRect))
    {
        ///paint the report
        painter.restore();
        painter.save();
        painter.translate(0, headerRect.height()-currentRect.y());
        ///if less difficult, do 2 translate (headerRect.height and currentRect.y)
        tdContent->drawContents(&painter, currentRect);


        ///paint the confidential
        bool confidential = true;
        if (confidential)
        {
            painter.restore();
            painter.save();
            painter.translate(0, m_writer->height()-30);
            painter.rotate(300);
            painter.setOpacity(0.5);
            tdConfidential->drawContents(&painter, confidentialRect);
        }

        ///paint the header and footer
        painter.restore();
        painter.save();
        tdHeader->drawContents(&painter, headerRect);
        painter.translate(0, headerRect.height());
        painter.translate(0, contentSize.height());
        tdFooter->drawContents(&painter, footerRect);

        currentRect.translate(0, currentRect.height());
        if (currentRect.intersects(contentRect))
        {
            m_writer->newPage();
        }
    }

    if (painter.end()){
        QTime chrono;
        chrono.start();
        while( chrono.elapsed() < 500 ){   }

        QDesktopServices::openUrl(QUrl("file:"+m_fileName));

    }
}
