#ifndef SQUARE_H
#define SQUARE_H

/*
The class for creating a square
*/

#include "Model/myshapes.h"

class Square:public MyShapes{
public:
    Square();
    void CreateObject(QImage *image,const QPoint &lastPoint,const QPoint &endPoint) override;
    QPainter painter;
};

#endif // SQUARE_H
