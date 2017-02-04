import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QMLReports 1.0
import Qt.labs.platform 1.0

ApplicationWindow {
    id: mainApp
    visible: true
    width: 200
    height: 100
    title: qsTr("QMLReports")

    property string docLocation: StandardPaths.writableLocation(StandardPaths.DocumentsLocation).toString().split("file://").pop()

    property string table:"
<table border=1 width=100%>
    <tr>
        <td>Test</td><td>of</td><td>Table</td>
    </tr>
    <tr>
        <td colspan='3' align='center'>This is a second line with colspan</td>
    </tr>
    <tr>
        <td>Test</td><td>of</td><td>Table</td>
    </tr>
    <tr>
        <td colspan='3' align='center'>This is a second line with colspan</td>
    </tr>
    <tr>
        <td>Test</td><td>of</td><td>Table</td>
    </tr>
    <tr>
        <td colspan='3' align='center'>This is a second line with colspan</td>
    </tr>

</table><br><br>";

    property string titleReport: "THIS IS AN EXAMPLE OF<br>QMLREPORTS<br><br>";
    property string textReport: "
This is the main text of the example of QMLReports. Here, we write a text with blue color, verdana family, 30 for size, justif aling. With QMLReports, create PDF files is very
simple and very fast. You can add header, footer and many contents. For each element you can use this properties : xOffsetMM, yOffsetMM, align, color, size, familiy, decoration,
weight, style and htmlText.<br><br>
<ul>
    <li>xOffsetMM :</li>
    <li>yOffsetMM :</li>
    <li>align :</li>
    <li>color :</li>
    <li>size :</li>
    <li>family :</li>
    <li>decoration :</li>
    <li>weight :</li>
    <li>style :</li>
    <li>htmlText :</li>
</ul><br><br>
";

    property string textReport2: "Qt Quick and QML provide an easy way to rapidly develop customized,
reusable components entirely within QML. As these components grow in complexity, performance and maintainability
often suffer, a drawback that is especially noticeable on low-powered embedded and mobile devices.
In addition, some specialized components simply cannot be implemented by combining existing Qt Quick items in QML.
For these cases, Qt Quick provides access to its underlying OpenGL scene graph via a C++ API.
Components created this way are more closely aligned to the underlying scene graph architecture allowing
improved performance and a cleaner implementation.
<br><br>
Qt Quick provides a flexible and easy-to-use framework for developing a wide range of applications from
automotive HMIs to interactive desktop applications. Under the hood, it uses an OpenGL scene graph for rendering,
allowing advanced effects and fluid animations even on low-powered  systems. Complex components written entirely in
QML can cause noticeable performance problems especially on these low-powered systems. Qt Quick provides a C++ API
to directly access its underlying scene graph for creating optimized components with better encapsulation.
These components can then be reused from QML in the same way as the built-in Qt Quick items.
<br><br>
The focus of this talk will be describing the steps necessary to create a Qt Quick component using C++ and OpenGL.
We will start with a custom component written entirely in QML and point out the performance and maintenance problems
with this approach. We will then reimplement this component in C++ and OpenGL, step-by-step, so that by the end you’ll
know enough to create your own C++ Qt Quick components. Finally we’ll compare the resulting component’s implementation
and performance against the original to see the improvement. I will also briefly mention the QtQuickFrameBufferObject as
an alternative and discuss when you would use it instead of the scene graph API.
<br><br>
The talk is aimed at developers with minimal OpenGL experience. It will briefly introduce enough of the basic OpenGL
concepts to get you started writing a custom Qt Quick item.<br><br><br>


<div style='font-size:20px'>KD Reports creates all kinds of reports from within Qt applications.</div>
<br><br>
KD Reports generates printable and exportable reports from code and from XML descriptions.
Reports may contain text paragraphs, tables, headlines, charts, headers and footers, and more.
<br><br>
Creating Reports out of Qt Applications Reporting is a very common task in almost all applications.
From the visualization of database contents in printouts to the creation of invoices or ID cards,
it is all about formatting information for printing.
<br><br>
KD Reports is a developer tool used in source code, but it allows using templates that are created by design staff.
This way, updating reports does not necessarily require code changes.  KD Reports is able to retrieve data for reports
from databases.  Also, it interfaces to Qt’s Model-View technology to access existing application model data.
<br><br>
A report often spans multiple pages, or elements of it need to be placed at specific locations to be printed in forms.
KD Reports provides page-breaking and endless paper support.  It also supports exact measurements for the placement of
elements in form cells.  Tables that span multiple pages can have repeating header rows assigned.
Those rows will be printed on top of every page the tables spans.
<br><br>
Watermarks can be used to add company logos or classification marks to documents.
They appear behind the report contents on every page.  Headers and footers can contain images or other elements.

The created reports can be shown in a preview dialog that is part of KD Reports.
They can be saved to PDF files or sent directly to a printer.
<br><br>
<div style='font-size:20px'>Creating a Report</div><br><br>

Creating a report always starts with creating a KDReports::Report object.  Then, there are two basic modes of operation:
<ul>
    <li>Elements like text blocks and images are created programmatically.
        The created elements form sequences that are either inlined or stacked as block (similar to HTML formatting rules).</li>
    <li>The report is initialized from an XML template. Then, the programmer fills in parts like table cell contents.
        In this mode, the programmer is less concerned with the actual formatting.  External designers or marketing and sales
        staff can be tasked with creating the report structure.</li>
</ul>

<div style='font-size:20px'>Elements of a Report</div>
<br><br>
Reports may contain any number of supported elements.  Developers can also add their own custom element types.
Element types that are shipped with KD Reports include:
<ul>
    <li>Images: Images can be loaded from external sources or created using Qt’s painting classes.
        All image formats supported by Qt or external image format plug-ins can be used.
    </li>
    <li>Text Paragraphs: Text can be inlined or block formatted.  Text paragraphs support all usual style
        options that developers expect (left, right, justified, or centered formatting) and all possible font style attributes.
        Text blocks can be nested to allow a part of a paragraph to have highlighted formatting, for example.
    </li>
    <li>Tables: Tables can be created from multiple sources of data (programmatically, from Model-View models,
        and from SQL databases).  Table cells can be individually formatted.  Cells can contain other elements,
        such as images.
    </li>
    <li>Charts: Charts are integrated if KDAB’s KD Chart package is available.  If integrated, charts can be used anywhere
        images could be.  Since KD Chart uses Model-View as well, creating chart elements that visualize
        table contents is easy.
    </li>
    <li>Preview Dialog: KD Reports ships with a preview dialog that can be used to give end users options on how to
        store or print the created reports.
    </li>
</ul>
";



    Report {
        id: qmlReport
        fileName: docLocation+"/test.pdf"
        header: logo
        contents:[titleContent, tableContent, textContent, textContent2, tableContent, textContent, textContent2, tableContent, textContent, textContent2, tableContent, textContent2]
        footer: footer
        resolution: 96
        model: ":/model.html"
        modelStyle: ":/style.css"
        dataModel: [["val1", "Qt Quick"], ["val2", "QML"]]
        // Add confidential property
    }

    ReportHeader {
        id: logo
        htmlText: "<img height=100 src='qrc:/img/Qt.png'>"
        align: "left"
    }

    ReportFooter {
        id: footer
        yOffsetMM: 5
        //center: true
        align: "right"
        htmlText: "
<div style='color:blue ; font-family:verdana ; font-size:10px ;'>Ceci est un pied de page</div><br>
<img height=30 src='qrc:/img/kdab.jpeg'>"
    }

    ReportContent {
        id: titleContent
        htmlText: titleReport
        size: 16
        weight: "bold"
        family: "helvetica"
        align: "center"
        yOffsetMM: 15   // probleme de gestion de cette property
    }

    ReportContent {
        id: tableContent
        htmlText: table
        size: 10
        family: "verdana"
        style: "italic"
    }

    ReportContent {
        id: textContent
        htmlText: textReport
        size: 12
        family: "verdana"
        color: "blue"
        align: "justify"
    }

    ReportContent {
        id: textContent2
        htmlText: textReport2
        size: 9
        family: "verdana"
        color: "green"
        align: "justify"
    }


    Button {
        id: btn
        x: 10; y: 10
        text: "print"
        onClicked: {
            qmlReport.print()
        }
    }
}
