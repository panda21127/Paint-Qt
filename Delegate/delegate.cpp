#include "Delegate/delegate.h"

#include <QMessageBox>
#include <QAction>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>

Delegate::Delegate(View &viewport)
{
    scribbleArea = new ScribbleArea;
    viewport.setCentralWidget(scribbleArea);
    viewport.openAct->setShortcuts(QKeySequence::Open);
    connect(viewport.openAct,&QAction::triggered,this,&Delegate::open);
    foreach(QAction *action,viewport.saveAsActs){
            connect(action,&QAction::triggered,this,&Delegate::save);
        }

    connect(viewport.penColor,&QAction::triggered,this,&Delegate::penColor);
    connect(viewport.penWidth,&QAction::triggered,this,&Delegate::penWidth);

    connect(viewport.info,&QAction::triggered,this,&Delegate::about);
    connect(viewport.infoQT,&QAction::triggered,qApp,&QApplication::aboutQt);
}

void Delegate::open(){
    //if(maybeSave()){
        QString filename = QFileDialog::getOpenFileName(scribbleArea,tr("Open File"),QDir::currentPath());
        if(!filename.isEmpty()){
            scribbleArea->openImage(filename); //&&&&&
        }
    //}
}

void Delegate::save(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void Delegate::penColor(){
    QColor newColor = QColorDialog::getColor(Qt::white);
    if(newColor.isValid()){
        scribbleArea->setPenColor(newColor);
    }
}

void Delegate::penWidth(){
    bool ok;
    int newWidth = QInputDialog::getInt(scribbleArea,tr("Scribble"),tr("Select pen width: "),scribbleArea->getPenWidth(),1,50,1,&ok);
    if(ok){
        scribbleArea->setPenWidth(newWidth);
    }
}

void Delegate::about(){
    QMessageBox::about(new QWidget,tr("About Scribble"),tr("<p>The <b>Scribble</b> example is awesome </p>"));
}

bool Delegate::saveFile(const QByteArray &fileFormat){
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(scribbleArea,tr("Save As"),initialPath,tr("%1 Fiels (*.%2);; All Files(*)")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    }else{
        return scribbleArea->saveImage(fileName,fileFormat.constData());
    }

}
