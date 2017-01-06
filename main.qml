import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QMLReports 1.0

ApplicationWindow {
    id: mainApp
    visible: true
    width: 200
    height: 100
    title: qsTr("QMLReports")

    /*Report {
        fileName: "/Users/charlie/test.pdf"
    }
    */


    Reports {
        id: reports
        fileName: "/Users/charlie/test.pdf"
        logoHtml: "<img src='qrc:/img/Qt.png'>"
        footerHtml: "
<div style='color:blue ; font-family:verdana ; font-size:30px ;'>Ceci est un pied de page</div><br>
<img src='qrc:/img/kdab.jpeg'>"

        contentHtml1:
"<div style='color:blue ; font-family:verdana ; font-style:italic ; font-size:30px ; font-weight:bold ; text-decoration:overline ; ' >
K<sub>max</sub>=K<sub>2</sub> &middot; <br><br><br><br><b>3fd</b>fdsufhufuishfcuifhuicnfgdfjgfsdfehfiuevfvvfgfg   dfhzeiufezui huifheiufh huihfeiuf huiehguiehr
kdfdjhff hgiheh hfguhgjhe hgrehgh<br><br><br>rgjhiher ghirhgierh ghirhgi gh ghrgh hrhgk h rghrekgherk
<br><br><br><br><br><br><br>
<table border=1>
     <tr><td>Toto10</td><td>Toto11</td></tr>
     <tr><td valign='middle'>Toto20</td><td align='right'>super mega <br>Toto21</td></tr>
     <tr><td colspan='2' align='center'>Toto3</td></tr>
</table><br>
 <img src=':/img/Qt.png'><br><br><br><br><br><br><br><br><br><br><br><br><br><br></div>";

        contentHtml2: "
<div style='color:blue ; font-family:verdana ; font-style:italic ; font-size:30px ; font-weight:bold '>
para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2
<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2para2
<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2<br>Para2para2
<br>Para21<br>Para22<br>Para23<br>Para24<br>Para25<br>Para26<br>Para27<br>Para28
</div>";
    }


    Button {
        x: 10; y: 10
        text: "print"
        onClicked: {
            reports.test();
            //reports.print()
        }
    }
}