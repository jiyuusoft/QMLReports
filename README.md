# QMLREPORTS

QMLReport allow to create a PDF file from a QML code.
See licence to use.

---------------------------------------------
### 1 - HOW GET AND INSTALL QMLREPORTS

#### 1.1 - GET QMLREPORTS :

Clone or download QMLReports from git :

    https://github.com/jiyuusoft/QMLReports

or

    git clone https://github.com/jiyuusoft/QMLReports.git

============================================
#### 1.2 - INSTALL FOR DESKTOP DEVICE (tested on Mac) :

In the folder downloaded :
    
    qmake
    make
    sudo make install
 
============================================
#### 1.3 - INSTALL FOR ANDROID DEVICE :
Paste the folder downloaded in your project and add in your *.pro file this lines:

    QMLREPORTSDIR = Path_to_source_of_QMLReports
    include($${QMLREPORTSDIR}/QMLReports.pri)


============================================
#### 1.4 - HOW INITIALIZE QMLREPORTS :

Here an example of your main file (main.cpp), with source of QMLReports in subdirectory QMLReports :


    #include <QGuiApplication>
    #include <QQmlApplicationEngine>
    #include <QStandardPaths>

    #include "QMLReports/qmlreports.h"


    int main(int argc, char *argv[])
    {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        QMLReports report;

        QQmlApplicationEngine engine;
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));

        return app.exec();
    }


---------------------------------------------
### 2 - HOW TO USE QMLREPORTS :

In your QML file, add thise line :
```
import QMLReports 1.x   //(currently x = 0)
```

Four components are available :
   - Report
   - ReportHeader
   - ReportFooter
   - ReportContent

============================================
#### 2.1 - Report  :

A Report's properties which are available are :

    fileName : -string : path of pdf File-
    margins: -float-
    header : -ReportHeader--
    contents: -list of ReportContent-
    footer: -ReportFooter-
    resolution: -int-
    model: -string: path of html file-
    modelStyle: -string: path of css file-
    dataModel: -list of list with 2 elements eg :[["key1", "Val1"], ["key2", "Val2"]]-
    confidential: -bool-

Note : if you use model, the contents property are disable.


Can contain one `ReportHeader`, one `ReportFooter` and one or many `ReportContent`.

============================================
#### 2.2 - ReportHeader, ReportFooter, ReportContent  :

Currently, ReportHeader, ReportFooter and ReportContent inherit of the same object : QReportsElement. This properties are : 

```
color: //string
family: //string
style: *string*
weight: *string*
decoration: *string*
htmlText: *string*
align: *string*
xOffsetMM: *float*
yOffsetMM: *float*
size: *int*
```

The properties color, family, style, weight, decoration, align are html tag. See http://doc.qt.io/qt-5/richtext-html-subset.html for more informations

