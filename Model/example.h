#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "Model/scribblearea.h"

#include <QThread>

class Example: public QThread
{
public:
    explicit Example(QString threadName);
    void setScribbleArea(ScribbleArea *area){ scribbleArea = area;};

public slots:
    void run();
private:
    ScribbleArea *scribbleArea;
    QString name;
};

#endif // EXAMPLE_H
