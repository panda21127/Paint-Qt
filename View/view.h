#ifndef VIEW_H
#define VIEW_H

/*
The class for creating and displaying all buttons
*/

#include "Model/scribblearea.h"

#include <QActionGroup>
#include <QRadioButton>
#include <QMainWindow>

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();
    //File
    QMenu *save;
    QList<QAction*> saveAsActs; //
    QAction * saveConfig;
    QAction * createNew;
    QAction * openAct;

    //Pen
    QAction * drawPen;
    QAction * penColor;
    QAction * penWidth;
    QAction * brushActive;
    //QRadioButton * alignmentGroup;

    //Shapes
    QAction * drawLine;
    QAction * ellipse;
    QAction * square;

    //Specidic Shapes
    QAction * drawSpecifiSquare;
    QAction * drawSpecifiElipse;
    QAction * lasso;

    //Examole
    QAction * exampleMenu;

    //Information
    QAction * info;
    QAction * infoQT;
private:
    void createMenu(); // creating Menubar
    void arrayActions(); // creating a format selection for saving an image

    QMenu *fileMenu;
    QMenu *penMenu;
    QMenu *shapes;
    QMenu *specifiShapes;
    QMenu *informationMenu;

};
#endif // VIEW_H
