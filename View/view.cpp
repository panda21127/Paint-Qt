#include "View/view.h"
#include "ui_view.h"

#include <QPainter>
#include <QPaintEvent>
#include <QImageWriter>

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    createMenu();
    setWindowTitle(tr("Paint"));
    resize(800,500);
}

void View::arratactions(){
    foreach(QByteArray format,QImageWriter::supportedImageFormats()){
            QString text = tr("%1...").arg(QString(format).toUpper());
            QAction *action=new QAction(text,this);
            action->setData(format);
            saveAsActs.append(action);
        }
}

void View::createMenu(){
    fileMenu = new QMenu(tr("&File"),this);
    save = new QMenu(tr("Save as ..."),this);
    arratactions();
    foreach(QAction *action,saveAsActs){
            save->addAction(action);
        }

    saveConfig = new QAction(tr("Save Config"),this);
    openAct = new QAction (tr("&Open"),this);
    openAct->setShortcuts(QKeySequence::Open);

    fileMenu->addMenu(save);
    fileMenu->addAction(saveConfig);
    fileMenu->addSeparator();
    fileMenu->addAction(openAct);

    penMenu = new QMenu(tr("&Pen"),this);
    penColor = new QAction(tr("Color"),this);
    penWidth = new QAction(tr("Width"),this);
    penMenu->addAction(penColor);
    penMenu->addAction(penWidth);

    exampleMenu = new QAction(tr("&Example"),this);

    informationMenu = new QMenu(tr("&Information"),this);
    info = new QAction(tr("Info"),this);
    infoQT = new QAction(tr("InfoQT"),this);
    informationMenu->addAction(info);
    informationMenu->addAction(infoQT);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(penMenu);
    menuBar()->addAction(exampleMenu);
    menuBar()->addMenu(informationMenu);
}


