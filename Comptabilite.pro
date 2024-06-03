#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT       += network
QT += axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        SMTPClient/email.cpp \
        SMTPClient/emailaddress.cpp \
        SMTPClient/smtpclient.cpp \
        comptabilite_CURD.cpp \
        comptabilite_metiers.cpp \
        main.cpp \
        mainwindow.cpp \
        qrcode.cpp \
        sdf_crud.cpp \
        service_crud.cpp \
        table_don.cpp

HEADERS += \
    QrCode.hpp \
    SMTPClient/email.h \
    SMTPClient/emailaddress.h \
    SMTPClient/smtpclient.h \
        comptabilite_CURD.h \
        comptabilite_metiers.h \
        mainwindow.h \
        sdf_crud.h \
        service_crud.h \
        table_don.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    SMTPClient/SMTPClient.pri \
    qmail-master/.gitignore \
    qmail-master/LICENSE \
    qmail-master/README.md \


SUBDIRS += \
    qmail-master/QMail.pro \
