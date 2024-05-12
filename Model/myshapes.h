#ifndef MYSHAPES_H
#define MYSHAPES_H

/*
The abstract class of shapes
*/

#include <QPoint>
#include <QPainter>
#include <QColor>

class MyShapes
{
public:
    virtual void CreateObject(QImage *image,const QPoint &lastPoint,const QPoint &endPoint) = 0; //function for creating shapes

    void setPenWidth(int width_new){ width = width_new;};

    void setPenColor(QColor color_new){ color = color_new;};

    void setBrushActive(bool brushActive_new){ brushActive = brushActive_new;};

protected:
    QColor color;
    int width;
    bool brushActive = false;
};

#endif // MYSHAPES_H
