#include "Model/Shapes/elipse.h"

Elipse::Elipse(){}

void Elipse::CreateObject(QImage *image,const QPoint &lastPoint,const QPoint &endPoint){
    QPainter painter(image);
    painter.setPen(QPen(color,width,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if(brushActive){
        QBrush brush(color,Qt::SolidPattern);
        painter.setBrush(brush);
    }
    painter.drawEllipse(lastPoint.x(),lastPoint.y(),endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
}
