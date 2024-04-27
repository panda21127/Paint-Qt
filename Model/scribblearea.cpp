#include "Model/scribblearea.h"

#include <iostream>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QColor>
#include <QThread>

ScribbleArea::ScribbleArea(QWidget *parent):QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    index = 0;
    if(!loadConfig()){
        myPenWidth = 10;
        myPenColor = Qt::black;
    }
}

bool ScribbleArea::openImage(const QString &fileName){
    QImage loadedImage;
    if(!loadedImage.load(fileName)){
        return false;
    }
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage,newSize);
    image = loadedImage;
    setModified(false);
    update();
    return true;
}

bool ScribbleArea::saveImage(const QString &fileName,const char *fileFormat){
    QImage visibleImage = image;
    resizeImage(&visibleImage,size());
    if(visibleImage.save(fileName,fileFormat)){
        modified = false;
        return true;
    }else{
        return false;
    }
}

bool ScribbleArea::loadConfig(){
    QFile file;
    //globalPath = QFileDialog::getOpenFileName(nullptr,"",QDir::currentPath() + "/../Paint-Qt/Config","*.json");
    //file.setFileName(globalPath);
    file.setFileName(QDir::currentPath() + "/../Paint-Qt/Config/PEN.json");
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        if(docError.errorString().toInt() == QJsonParseError::NoError){
            QJsonObject jsonObj = doc.object();
            //"penColor" : "blue",
            //"penWidth" : 30
            QString color;
            color = jsonObj.value("penColor").toString();
            myPenColor.setNamedColor(color);
            myPenWidth = jsonObj.value("penWidth").toInt();
            //doc.object()["penWidth"] = 10;
            file .close();
            return true;
        }
        else{
            QMessageBox::information(nullptr,"info","Файл содержит ошибку");
            return false;
        }
    }
    else{
        QMessageBox::information(nullptr,"info","Файл не открыт на чтенеи");
        return false;
    }
}

void ScribbleArea::saveConfigJSON(){
    QFile file;
    //globalPath = QFileDialog::getOpenFileName(nullptr,"",QDir::currentPath() + "/../Paint-Qt/Config","*.json");
    //file.setFileName(globalPath);
    file.setFileName(QDir::currentPath() + "/../Paint-Qt/Config/PEN.json");
    if(file.open(QIODevice::WriteOnly|QFile::Text)){
        QJsonObject jsonObj = doc.object();
        jsonObj.insert("penColor",QJsonValue::fromVariant(myPenColor));
        jsonObj.insert("penWidth",QJsonValue::fromVariant(myPenWidth));
        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        QTextStream stream (&file);
        stream<<jsonString;
        qDebug()<<jsonObj["penWidth"].toInt();
        //file.write(doc.toJson());
        file .close();
    }
    else{
        QMessageBox::information(nullptr,"info","Файл не открыт на чтенеи");
    }
}

void ScribbleArea::clearImage(){
    image.fill(qRgb(255,255,255));
    setModified(true);
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        lastPoint = event->pos();
        setScribbling(true);
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event){

    switch(index){
    case 0:
           if((event->buttons()& Qt::LeftButton)&& isScribbling()){
                drawLineTo(event->pos());
           }
           break;
    case 1:
           if((event->buttons()& Qt::LeftButton)&& isScribbling()){
               setModified(true);
           }
           break;
    case 2:
           if((event->buttons()& Qt::LeftButton)&& isScribbling()){
               setModified(true);
           }
           break;
    case 10:
           if((event->buttons()& Qt::LeftButton)&& isScribbling()){
               drawSpecifiElipse(event->pos());
               setModified(true);
           }
           break;
    case 11:
           if((event->buttons()& Qt::LeftButton)&& isScribbling()){
               drawSquare(event->pos());
               setModified(true);
           }
           break;
    case 12:
           if((event->buttons()& Qt::LeftButton)&& isScribbling()){
               drawLasso(event->pos());
               setModified(true);
           }
           break;
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event){
    switch(index){
    case 0:
        if((event->buttons() != Qt::LeftButton)&& isScribbling()){
            drawLineTo(event->pos());
            setScribbling(false);
        }
        break;
    case 1:
        if((event->buttons() != Qt::LeftButton)&& isScribbling()){
            drawEllipse(event->pos());
            setScribbling(false);
        }
        break;
    case 2:
        if((event->buttons() != Qt::LeftButton)&& isScribbling()){
            drawSquare(event->pos());
            setScribbling(false);
        }
        break;
    case 10:
        if((event->buttons() != Qt::LeftButton)&& isScribbling()){
            drawSpecifiElipse(event->pos());
            setScribbling(false);
        }
        break;
    case 11:
        if((event->buttons() != Qt::LeftButton)&& isScribbling()){
            drawSquare(event->pos());
            setScribbling(false);
        }
        break;
    case 12:
        if((event->buttons() != Qt::LeftButton)&& isScribbling()){
            drawLasso(event->pos());
            setScribbling(false);
        }
        break;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawImage(dirtyRect,image,dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event){
    if(width() > image.width() || height() > image.height()){
        int newWidth = qMax(width() + 128,image.width());
        int newHeight = qMax(height() + 128,image.height());
        resizeImage(&image,QSize(newWidth,newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::resizeImage(QImage *image,const QSize &newSize){
    if(image->size() == newSize){
        return;
    }
    QImage newImage(newSize,QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0),*image);
    *image = newImage;
}

void ScribbleArea::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint,endPoint);
    //painter.drawEllipse(lastPoint.x(),lastPoint.y(),endPoint.x(),endPoint.y());
    setModified(true);
    int rad = (getPenWidth() / 2) + 2;
    update(QRect(lastPoint,endPoint).normalized().adjusted(-rad,-rad,+rad,+rad));
    lastPoint=endPoint;
}

void ScribbleArea::drawSpecifiElipse(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawEllipse(lastPoint.x(),lastPoint.y(),endPoint.x(),endPoint.y());
    setModified(true);
    update();
    lastPoint=endPoint;
}

void ScribbleArea::drawLasso(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint,endPoint);
    setModified(true);
    update();
}

void ScribbleArea::drawEllipse(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawEllipse(lastPoint.x(),lastPoint.y(),endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
    setModified(true);
    update();
}

void ScribbleArea::drawSquare(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawRect(lastPoint.x(),lastPoint.y(),endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
    setModified(true);
    update();
}

void ScribbleArea::drawExample(){
    QPainter painter(&image);
    painter.setPen(QPen(Qt::black,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    for(int i=10;i<150;i++){
        painter.drawLine(i, 30, i + 1, 30);
        repaint();
        QThread::msleep(10);
    }
    for(int i=30;i<120;i++){
        painter.drawLine(150, i, 150, i+1);
        repaint();
        QThread::msleep(10);
    }
    for(int i=150;i>10;i--){
        painter.drawLine(i, 120, i-1, 120);
        repaint();
        QThread::msleep(10);
    }
    for(int i=120;i>30;i--){
        painter.drawLine(10, i, 10, i-1);
        repaint();
        QThread::msleep(10);
    }
}
