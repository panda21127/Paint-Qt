QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Delegate/delegate.cpp \
    Model/Shapes/elipse.cpp \
    Model/Shapes/line.cpp \
    Model/Shapes/square.cpp \
    Model/example.cpp \
    Model/scribblearea.cpp \
    Model/zoomwidget.cpp \
    View/view.cpp \
    main.cpp \

HEADERS += \
    Delegate/delegate.h \
    Model/Shapes/elipse.h \
    Model/Shapes/line.h \
    Model/Shapes/square.h \
    Model/example.h \
    Model/myshapes.h \
    Model/scribblearea.h \
    Model/zoomwidget.h \
    View/view.h \

FORMS += \
    view.ui

TRANSLATIONS += \
    Paint_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
