QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/menu.cpp \
    Model/example.cpp \
    Model/file.cpp \
    Model/information.cpp \
    Model/penedit.cpp \
    Model/scribblearea.cpp \
    View/mainwindow.cpp \
    main.cpp \

HEADERS += \
    Controller/menu.h \
    Model/Shapes.h \
    Model/example.h \
    Model/file.h \
    Model/information.h \
    Model/penedit.h \
    Model/scribblearea.h \
    View/mainwindow.h \


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
