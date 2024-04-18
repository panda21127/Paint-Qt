#include "Model/penedit.h"
#include "View/mainwindow.h"

#include <QInputDialog>
#include <QColorDialog>
#include <QObject>
#include <QTextStream>

#include <iostream>

PenEdit::PenEdit()
{
    colorEdit = new QAction(QObject::tr("Color ..."));

    widthEdit = new QAction(QObject::tr("Width ..."));
    //connect(widthEdit,&QAction::triggered,new MainWindow,SLOT(getScribbleArea_slots));
    //printf("Error destroy 2");

}

void PenEdit::penColor(){
    QColor newColor = QColorDialog::getColor();
    connect(this, SIGNAL(sendColor(QColor)),new MainWindow,SLOT(setColor_slots(QColor)));
    QTextStream cout(stdout,QIODevice::WriteOnly);
    std::cout<<"Our colour "<< newColor.colorNames<< std::endl;
    emit sendColor(newColor);
    printf("Error destroy 3");
    if(newColor.isValid()){
        //scribbleArea->setPenColor(newColor);
        sendColor(newColor);
    }
}

void PenEdit::penWidth(ScribbleArea *scribbleArea){
    bool ok;
    int newWidth = QInputDialog::getInt(new QWidget,tr("Scribble"),tr("Select pen width: "),scribbleArea->GetpenWidth(),1,50,1,&ok);
    printf("Error destroy 3");
    if(ok){
        scribbleArea->setPenWidth(newWidth);
    }
}

PenEdit::~PenEdit()
{
    delete colorEdit;
    delete widthEdit;
}
