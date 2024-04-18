#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>
#include <QAction>

class Example:public QObject
{
    Q_OBJECT
public:
    Example();
    ~Example() {}; //TODO
};

#endif // EXAMPLE_H
