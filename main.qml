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

    property string table:
"<table border=1 width=100%>
    <tr>
        <td colspan='2' align='center'>An example of table</td>
    </tr>
    <tr>
        <td rowspan='2' valign='middle' align='center'>rowspan and colspan work</td>
        <td align='right'>you can easaly create your tab</td>
    </tr>
    <tr>
        <td align='center'>Last Ce</td>
    </tr>
</table><br><br><br>";

    property string titleReport: "THIS IS AN EXAMPLE OF<br>QMLREPORTS<br><br>";  //revoir l'utilisation de la balise center en tant que property
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
</ul>
<br><br><br><br><br><br><br><br>";

    property string textReport2: "
This is a second text";


    Report {
        id: qmlReport
        fileName: docLocation+"/test.pdf"
        header: logo
        contents:[titleContent, tableContent, textContent, textContent2]
        footer: footer
        resolution: 900
        // Add confidential property
    }

    ReportHeader {
        id: logo
        htmlText: "<img src='qrc:/img/Qt.png'>"
        align: "left"
    }

    ReportFooter {
        id: footer
        yOffsetMM: 5
        //center: true
        align: "right"
        htmlText: "
<div style='color:blue ; font-family:verdana ; font-size:30px ;'>Ceci est un pied de page</div><br>
<img src='qrc:/img/kdab.jpeg'>"
    }

    ReportContent {
        id: titleContent
        htmlText: titleReport
        size: 10
        weight: "bold"
        family: "helvetica"
        align: "center"
        yOffsetMM: 15   // probleme de gestion de cette property
    }

    ReportContent {
        id: tableContent
        htmlText: table
        size: 30
        family: "verdana"
        style: "italic"
    }

    ReportContent {
        id: textContent
        htmlText: textReport
        size: 10
        family: "verdana"
        color: "blue"
        align: "justify"
    }

    ReportContent {
        id: textContent2
        htmlText: textReport2
        size: 10
        family: "verdana"
        color: "green"
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
