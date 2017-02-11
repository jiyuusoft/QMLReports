PROG = QMLReports

QT += qml printsupport

TEMPLATE = lib

CONFIG += staticlib \
    debug_and_release \
    c++11 \
    create_prl \
    link_prl \


Release:DESTDIR = release
Debug:DESTDIR = debug

SOURCES += qmlreports.cpp \
    qmlreportsfooter.cpp \
    qmlreportscontent.cpp \
    qmlreportselement.cpp \
    qmlreportsconfidential.cpp \
    qmlreportsheader.cpp \

HEADERS += qmlreports.h \
    qmlreportsfooter.h \
    qmlreportscontent.h \
    qmlreportselement.h \
    qmlreportsconfidential.h \
    qmlreportsheader.h


headersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROG/
headersDataFiles.files = $$PWD/*.h
INSTALLS += headersDataFiles
                                  
                               
libraryFiles.path = $$[QT_INSTALL_LIBS]
CONFIG(debug, debug|release):libraryFiles.files += $$OUT_PWD/debug/*.a
CONFIG(debug, debug|release):libraryFiles.files += $$OUT_PWD/debug/*.prl
                               
CONFIG(release, debug|release):libraryFiles.files += $$OUT_PWD/release/*.a
CONFIG(release, debug|release):libraryFiles.files += $$OUT_PWD/release/*.prl
INSTALLS += libraryFiles
