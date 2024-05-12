#ifndef EXAMPLE_H
#define EXAMPLE_H

/*
The class somehow related to multithreading
*/

#include "Model/scribblearea.h"

#include <QThread>

class Example: public QThread
{
public:
    explicit Example(QString threadName);
    void setScribbleArea(ScribbleArea *area){ scribbleArea = area;};

public slots:
    void run(); // run thread program
private:
    ScribbleArea *scribbleArea;
    QString name;
};

#endif // EXAMPLE_H
