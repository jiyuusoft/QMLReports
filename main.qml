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


    Component.onCompleted: {
        console.log(dataLocation, docLocation)
    }



    property string contentHtml1:
        "K<sub>max</sub>=K<sub>2</sub> &middot; <br><br><br><br><b>3fd</b>fdsufhufuishfcuifhuicnfgdfjgfsdfehfiuevfvvfgfg   dfhzeiufezui huifheiufh huihfeiuf huiehguiehr
        kdfdjhff hgiheh hfguhgjhe hgrehgh<br><br><br>rgjhiher ghirhgierh ghirhgi gh ghrgh hrhgk h rghrekgherk
        <br><br><br><br><br><br><br>
        <table border=1>
             <tr><td>Toto10</td><td>Toto11</td></tr>
             <tr><td valign='middle'>Toto20</td><td align='right'>super mega <br>Toto21</td></tr>
             <tr><td colspan='2' align='center'>Toto3</td></tr>
        </table><br>
         <img src=':/img/Qt.png'><br><br><br><br><br><br><br><br><br><br><br><br><br><br>";

    property string contentHtml2:
        "para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2
<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2para2
<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2para2
<br>Para21<br>Para22<br>Para23<br>Para24<br>Para25<br>Para26<br>Para27<br>Para28
</div>";

    Report {
        id: qmlReport
        fileName: docLocation+"test.pdf"
        logo: logo
        contents:[content, content2, content, content2]
        footer: footer
    }


    ReportContent {
        id: content
        htmlText: contentHtml1
        size: 30
        family: "verdana"
        style: "italic"
    }

    ReportContent {
        id: content2
        htmlText: contentHtml2
        size: 30
        weight: "bold"
        family: "verdana"
        style: "italic"
        //align: "center"

    }

    ReportFooter {
        id: footer
        yOffsetMM: 5
        align: "center"
        htmlText: "
<div style='color:blue ; font-family:verdana ; font-size:30px ;'>Ceci est un pied de page</div><br>
<img src='qrc:/img/kdab.jpeg'>"
    }

    ReportLogo {
        id: logo
        htmlText: "<img src='qrc:/img/Qt.png'>"
        center: true
        align: "center"
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
