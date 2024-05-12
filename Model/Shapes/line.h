#ifndef LINE_H
#define LINE_H

/*
The class for creating a line
*/

#include "Model/myshapes.h"

class Line:public MyShapes{
public:
    Line();
    void CreateObject(QImage *image,const QPoint &lastPoint,const QPoint &endPoint) override;
    QPainter painter;
};

#endif // LINE_H
