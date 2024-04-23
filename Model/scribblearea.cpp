#include "Model/scribblearea.h"

#include <iostream>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QColor>

ScribbleArea::ScribbleArea(QWidget *parent):QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
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
    globalPath = QFileDialog::getOpenFileName(nullptr,"",QDir::currentPath() + "/../Paint-Qt/Config","*.json");
    file.setFileName(globalPath);
    //file.setFileName(QDir::currentPath() + "/../Paint-Qt/Config/PEN.json");
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

void  ScribbleArea::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);

    painter.setPen(QPen(getPenColor(),getPenWidth(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint,endPoint);
    setModified(true);
    int rad = (getPenWidth() / 2) + 2;
    update(QRect(lastPoint,endPoint).normalized().adjusted(-rad,-rad,+rad,+rad));
    lastPoint=endPoint;
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

    if((event->buttons()& Qt::LeftButton)&& isScribbling()){
        drawLineTo(event->pos());
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event){

    if((event->buttons() == Qt::LeftButton)&& isScribbling()){
        drawLineTo(event->pos());
        setScribbling(false);
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
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
