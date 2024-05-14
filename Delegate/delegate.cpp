#include "Delegate/delegate.h"

#include <QString>
#include <QMessageBox>
#include <QAction>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>

Delegate::Delegate()
{
        scribbleArea = new ScribbleArea;
        brushActive = false;
}

//Start
void Delegate::start(View &viewport){
    connect(viewport.openAct,&QAction::triggered,this,&Delegate::open);
    foreach(QAction *action,viewport.saveAsActs){
            connect(action,&QAction::triggered,this,&Delegate::save);
        }
    connect(viewport.saveConfig,&QAction::triggered,this,&Delegate::saveConfig);

    connect(viewport.createNew,&QAction::triggered,this,&Delegate::createNew);

    viewport.setCentralWidget(scribbleArea);
    viewport.openAct->setShortcuts(QKeySequence::Open);

    connect(viewport.drawPen,&QAction::triggered,this,&Delegate::drawPen);
    connect(viewport.penColor,&QAction::triggered,this,&Delegate::penColor);
    connect(viewport.penWidth,&QAction::triggered,this,&Delegate::penWidth);
    connect(viewport.brushActive,&QAction::triggered,this,&Delegate::ActiveBrush);

    connect(viewport.drawLine,&QAction::triggered,this,&Delegate::drawLine);
    connect(viewport.ellipse,&QAction::triggered,this,&Delegate::drawEllipse);
    connect(viewport.square,&QAction::triggered,this,&Delegate::drawSquare);

    connect(viewport.drawSpecifiElipse,&QAction::triggered,this,&Delegate::drawSpecificElipse);
    connect(viewport.drawSpecifiSquare,&QAction::triggered,this,&Delegate::drawSpecificSquare);
    connect(viewport.lasso,&QAction::triggered,this,&Delegate::drawLasso);

    connect(viewport.info,&QAction::triggered,this,&Delegate::about);
    connect(viewport.infoQT,&QAction::triggered,qApp,&QApplication::aboutQt);

    connect(viewport.exampleMenu,&QAction::triggered,this,&Delegate::startExample);
}

//File
void Delegate::save(){
    if(scribbleArea->isModified()){
        QAction *action = qobject_cast<QAction *>(sender());
        QByteArray fileFormat = action->data().toByteArray();
        if(saveFile(fileFormat)){
            QMessageBox::information(nullptr,"info","Файл сохранён");
        }
        else{
            QMessageBox::information(nullptr,"info","Файл не сохранён");
        }
    }
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

void Delegate::saveConfig(){
        scribbleArea->saveConfigJSON();
}

void Delegate::createNew(){
        scribbleArea->clearImage();
}

void Delegate::open(){
        QString filename = QFileDialog::getOpenFileName(scribbleArea,tr("Open File"),QDir::currentPath());
        if(!filename.isEmpty()){
            scribbleArea->openImage(filename); //&&&&&
        }
}

//Pen
void Delegate::penColor(){
    QColor newColor = QColorDialog::getColor(Qt::white);
    if(newColor.isValid()){
        scribbleArea->setPenColor(newColor);
    }
}

void Delegate::penWidth(){
    bool ok;
    int newWidth = QInputDialog::getInt(scribbleArea,tr("Width"),tr("Select pen width: "),scribbleArea->getPenWidth(),1,50,1,&ok);
    if(ok){
        scribbleArea->setPenWidth(newWidth);
    }
}

void Delegate::ActiveBrush(){
    brushActive = !brushActive;
    scribbleArea->ChangeBrushActive(brushActive);
}

//All Shapes
void Delegate::drawPen(){
        MyShapes *shape = new Line();
        scribbleArea->setIndex(2);
        scribbleArea->setShape(shape);
}

void Delegate::drawLine(){
        MyShapes *shape = new Line();
        scribbleArea->setIndex(0);
        scribbleArea->setShape(shape);
}

void Delegate::drawEllipse(){
        MyShapes *shape = new Elipse();
        shape->setBrushActive(brushActive);
        scribbleArea->setIndex(0);
        scribbleArea->setShape(shape);
}

void Delegate::drawSquare(){
        MyShapes *shape = new Square();
        shape->setBrushActive(brushActive);
        scribbleArea->setIndex(0);
        scribbleArea->setShape(shape);
}

void Delegate::drawSpecificElipse(){
        MyShapes *shape = new Elipse();
        shape->setBrushActive(brushActive);
        scribbleArea->setIndex(1);
        scribbleArea->setShape(shape);
}

void Delegate::drawSpecificSquare(){
        MyShapes *shape = new Square();
        shape->setBrushActive(brushActive);
        scribbleArea->setIndex(1);
        scribbleArea->setShape(shape);
}

void Delegate::drawLasso(){
        MyShapes *shape = new Line();
        scribbleArea->setIndex(1);
        scribbleArea->setShape(shape);
}

//Example
void Delegate::startExample(){
    //Example example("Thread");
    Example* example = new Example("Thread");
    example->setScribbleArea(scribbleArea);
    QThread* thread = new QThread;/* передаем список файлов для обработки */
    QThread* thread2 = new QThread;
    example->moveToThread(thread);
    //scribbleArea->moveToThread(thread2);
    connect(thread, &QThread::started, example, &Example::run);
    connect(thread2, &QThread::started, scribbleArea, &ScribbleArea::drawExample);
    thread->start();
    thread2->start();
    //example->run();
}

//Information
void Delegate::about(){
    QMessageBox::about(new QWidget,tr("About Paint"),tr("<p><b>Paint</b> вышел неплохим </p>"));
}


Delegate::~Delegate(){
        delete scribbleArea;
}
