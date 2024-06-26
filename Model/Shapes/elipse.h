#ifndef ELIPSE_H
#define ELIPSE_H

/*
The class for creating a elipse
*/

#include "Model/myshapes.h"

class Elipse:public MyShapes{
public:
    Elipse();
    void CreateObject(QImage *image,const QPoint &lastPoint,const QPoint &endPoint) override;
    QPainter painter;
};

#endif // ELIPSE_H
