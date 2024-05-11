#ifndef DELEGATE_H
#define DELEGATE_H

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
    void open();
    void save();
    void saveConfig();
    void createNew();
    void about();
    void penColor();
    void penWidth();

    void drawPen();
    void drawLine();
    void drawEllipse();
    void drawSquare();

    void drawSpecifiElipse();
    void drawSpecifiSquare();
    void drawLasso();

    void ActiveBrush();
    void startExample();
private:
    bool saveFile(const QByteArray &fileFormat);
    QPoint lastPoint;
    ScribbleArea *scribbleArea;
    bool brushActive;
};

#endif // DELEGATE_H
