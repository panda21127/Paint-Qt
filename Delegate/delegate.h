#ifndef DELEGATE_H
#define DELEGATE_H

/*
The class for connecting buttons to model functions, extending models
*/

#include "View/view.h"
#include "Model/scribblearea.h"
#include "Model/example.h"
#include "Model/Shapes/square.h"
#include "Model/Shapes/elipse.h"
#include "Model/Shapes/line.h"

#include <QWidget>

class Delegate: public QObject
{
    Q_OBJECT
public:
    Delegate();
    void start(View &viewport);
    ~Delegate();
private slots:
    //File
    void save();
    void saveConfig();
    void createNew();
    void open();

    //Pen
    void drawPen();
    void penColor();
    void penWidth();
    void ActiveBrush();

    //Shapes
    void drawLine();
    void drawEllipse();
    void drawSquare();

    //Specidic Shapes
    void drawSpecificElipse();
    void drawSpecificSquare();
    void drawLasso();

    //Example
    void startExample();

    //Information
    void about();
private:
    bool saveFile(const QByteArray &fileFormat);
    QPoint lastPoint;
    ScribbleArea *scribbleArea;
    bool brushActive;
};

#endif // DELEGATE_H
