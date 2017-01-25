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

bool QMLReports::confidential() const {return m_confidential;}
void QMLReports::setConfidential(const bool &confidential) {m_confidential = confidential;}



QMLReportsHeader *QMLReports::header() const
{
    return m_qmlHeader;
}

void QMLReports::setHeader(QMLReportsHeader *header)
{
    m_qmlHeader = header;
}

QMLReportsFooter *QMLReports::footer() const
{
    return m_qmlFooter;
}

void QMLReports::setFooter(QMLReportsFooter *footer)
{
    m_qmlFooter = footer;
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

void QMLReports::createHeader()
{
    m_tdHeader = new QTextDocument(this);
    QTextOption textOptionHeader;

    textOptionHeader.setWrapMode(QTextOption::WordWrap);
    m_tdHeader->setDefaultTextOption(textOptionHeader);
    m_tdHeader->setPageSize(m_rectPrinter.size());
    m_tdHeader->setHtml(setFormat(m_qmlHeader));
    m_headerSize = m_tdHeader->size();

}

void QMLReports::createFooter()
{
    m_tdFooter = new QTextDocument(this);
    QTextOption textOptionFooter;

    textOptionFooter.setWrapMode(QTextOption::WordWrap);
    m_tdFooter->setDefaultTextOption(textOptionFooter);
    m_tdFooter->setPageSize(m_rectPrinter.size());
    m_tdFooter->setHtml(setFormat(m_qmlFooter));
    m_footerSize = m_tdFooter->size();

    ///add Offset

}

void QMLReports::createConfidential()
{
    m_tdConfidential = new QTextDocument(this);
    QTextOption textOptionConfidential;

    textOptionConfidential.setWrapMode(QTextOption::WordWrap);
    m_tdConfidential->setDefaultTextOption(textOptionConfidential);
    m_tdConfidential->setPageSize(m_rectPrinter.size());
    m_tdConfidential->setHtml("<div style='color:OrangeRed  ; font-family:georgia ; font-style:normal ; "
                           "font-size:300px ; font-weight:normal ; text-decoration:none '><pre>C  O  N  F  I  D  E  N  T  I  A  L</pre></div>");

}

void QMLReports::addContent()
{
    for (int i=0; i < m_contents.length(); i++){
        QMLReportsContent *content = m_contents.at(i);
        m_totalHtml += setFormat(content);
    }


}


void QMLReports::print()
{
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
    m_rectPrinter;
    m_rectPrinter.setCoords(0, 0, m_writer->width(), m_writer->height());


    ///Limiter la taille de Header & Footer.
    createHeader();
    createFooter();
    createConfidential();

    ///Calculating the main document size for one page
    QSizeF contentSize(m_rectPrinter.width(), (m_rectPrinter.height() - m_headerSize.toSize().height() - m_footerSize.toSize().height()));

    ///Setting up the center page
    QTextDocument *tdContent = new QTextDocument(this);
    addContent();
    tdContent->setHtml(m_totalHtml);
    tdContent->setPageSize(contentSize);

    ///Setting up the rectangles for each section.
    QRectF headerRect = QRectF(QPoint(0,0), m_tdHeader->size().toSize());
    QRectF footerRect = QRectF(QPoint(0,0), m_tdFooter->size().toSize());
    QRectF confidentialRect = QRectF(QPoint(0,0), m_tdConfidential->size().toSize());
    QRectF contentRect = QRectF(QPoint(0,0), tdContent->size().toSize());    /// Main content rectangle.
    QRectF currentRect = QRectF(QPoint(0,0), contentSize.toSize());        /// Current main content rectangle.

    QPainter painter(m_writer);
    painter.save();

    while (currentRect.intersects(contentRect))
    {
        painter.restore();
        painter.save();
        painter.translate(0, headerRect.height()-currentRect.y());
        ///if less difficult, do 2 translate (headerRect.height and currentRect.y)
        tdContent->drawContents(&painter, currentRect);


        ///paint the confidential
        if (m_confidential)
        {
            painter.restore();
            painter.save();
            painter.translate(0, m_writer->height()-30);
            painter.rotate(300);
            painter.setOpacity(0.5);
            m_tdConfidential->drawContents(&painter, confidentialRect);
        }

        ///paint the header and footer
        painter.restore();
        painter.save();
        m_tdHeader->drawContents(&painter, headerRect);
        painter.translate(0, headerRect.height());
        painter.translate(0, contentSize.height());
        m_tdFooter->drawContents(&painter, footerRect);

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
