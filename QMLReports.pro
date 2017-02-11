PROG = QMLReports


QT += gui core qml printsupport
TEMPLATE = lib

CONFIG += staticlib \
    debug_and_release \
    c++11 \
    lib_bundle \
    create_prl \
    link_prl \


Release:DESTDIR = release
#Release:OBJECTS_DIR = release/.obj
#Release:MOC_DIR = build/release/.moc
#Release:RCC_DIR = build/release/.rcc
#Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
#Debug:OBJECTS_DIR = build/debug/.obj
#Debug:MOC_DIR = build/debug/.moc
#Debug:RCC_DIR = build/debug/.rcc
#Debug:UI_DIR = build/debug/.ui


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
