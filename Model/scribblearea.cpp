#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#include "Model/scribblearea.h"
#include <iostream>
#include <QTextStream>

ScribbleArea::ScribbleArea(QWidget *parent):QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::red;
}

void ScribbleArea::setPenColor( QColor newColor){
    QTextStream cout(stdout,QIODevice::WriteOnly);
    std::cout << "Our B-mask colour " << newColor.blue()<< std::endl;
    std::cout << "Our G-mask colour " << newColor.green()<< std::endl;
    std::cout << "Our R-mask colour " << newColor.red()<< std::endl;
    myPenColor=newColor;
}

void ScribbleArea::setPenWidth(int newWidth){
     myPenWidth=newWidth;
}

void ScribbleArea::clearImage(){
    image.fill(qRgb(255,255,255));
    modified = true;
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        lastPoint = event->pos();
        scribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons()& Qt::LeftButton)&& scribbling){
        drawLineTo(event->pos());
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event){
    if((event->buttons() == Qt::LeftButton)&& scribbling){
        drawLineTo(event->pos());
        scribbling = false;
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

void ScribbleArea::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
    QTextStream cout(stdout,QIODevice::WriteOnly);
    //std::cout<<"NOOt Our colour "<< myPenColor.blue()<< std::endl;

    std::cout<<"Our B-mask colour "<< myPenColor.blue()<< std::endl;
    std::cout<<"Our G-mask colour "<< myPenColor.green()<< std::endl;
    std::cout<<"Our R-mask colour "<< myPenColor.red()<< std::endl;
    painter.setPen(QPen(myPenColor,myPenWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint,endPoint);
    modified = true;
    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint,endPoint).normalized().adjusted(-rad,-rad,+rad,+rad));
    lastPoint=endPoint;
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
