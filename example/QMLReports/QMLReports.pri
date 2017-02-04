QT += gui core qml printsupport

CONFIG += c++11

SOURCES += $${QMLREPORTSDIR}/qmlreports.cpp \
    $${QMLREPORTSDIR}/qmlreportsfooter.cpp \
    $${QMLREPORTSDIR}/qmlreportscontent.cpp \
    $${QMLREPORTSDIR}/qmlreportselement.cpp \
    $${QMLREPORTSDIR}/qmlreportsconfidential.cpp \
    $${QMLREPORTSDIR}/qmlreportsheader.cpp \

HEADERS += $${QMLREPORTSDIR}/qmlreports.h \
    $${QMLREPORTSDIR}/qmlreportsfooter.h \
    $${QMLREPORTSDIR}/qmlreportscontent.h \
    $${QMLREPORTSDIR}/qmlreportselement.h \
    $${QMLREPORTSDIR}/qmlreportsconfidential.h \
    $${QMLREPORTSDIR}/qmlreportsheader.h
