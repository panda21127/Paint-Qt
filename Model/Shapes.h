#ifndef SHAPES_H
#define SHAPES_H

#include <QAction>
#include <QObject>

class Shape
{
public:
    virtual void createShape() = 0;
    virtual ~Shape() {};
};

#endif // SHAPES_H
