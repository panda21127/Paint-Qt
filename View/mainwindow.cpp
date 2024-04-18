#include "View/mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QTextStream>

MainWindow::MainWindow()
{
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    createMenu();
    setWindowTitle(tr("Paint"));
    resize(800,500);
}

void MainWindow::createMenu(){
    menu = new Menu();

    fileMenu = new QMenu(tr("&File"),this);
    foreach(QMenu *actionsMenu,menu->CreateFileMenu()){
        fileMenu->addMenu(actionsMenu);
    }
    foreach(QAction *action,menu->CreateFileAction()){
        fileMenu->addAction(action);
    }

    penMenu = new QMenu(tr("&Pen"),this);
    foreach(QAction *action,menu->CreatePenEdit()){
        penMenu->addAction(action);
    }
    /*
    exampleMenu = new QMenu(tr("&Example"),this);
    foreach(QAction *action,menu->CreateExample()){
        exampleMenu->addAction(action);
    }
    */
    informationMenu = new QMenu(tr("&Information"),this);
    foreach(QAction *action,menu->CreateInformation()){
        informationMenu->addAction(action);
    }

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(penMenu);
    //menuBar()->addMenu(exampleMenu);
    menuBar()->addMenu(informationMenu);
}

void MainWindow::setColor_slots(QColor color){
    QTextStream cout(stdout,QIODevice::WriteOnly);
    std::cout<<"colour "<< color.colorNames<< std::endl;
    std::cout<<"B-mask colour "<< color.blue()<< std::endl;
    std::cout<<"G-mask colour "<< color.green()<< std::endl;
    std::cout<<"R-mask colour "<< color.red()<< std::endl;
    scribbleArea->setPenColor(color);

};

void MainWindow::getScribbleArea_slots(){
    connect(this,SIGNAL(getScribbleArea_signal(ScribbleArea)),new PenEdit(),SLOT(penWidth(ScribbleArea)));
    emit getScribbleArea_signal(scribbleArea);
}
