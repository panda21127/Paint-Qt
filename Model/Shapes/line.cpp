#include "Model/Shapes/line.h"

Line::Line(){}

void Line::CreateObject(QImage *image,const QPoint &lastPoint,const QPoint &endPoint){
    QPainter painter(image);
    painter.setPen(QPen(color,width,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if(brushActive){
        QBrush brush(color,Qt::SolidPattern);
        painter.setBrush(brush);
    }
    painter.drawLine(lastPoint,endPoint);
}
