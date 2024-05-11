#ifndef VIEW_H
#define VIEW_H

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
    QMenu *save;
    QList<QAction*> saveAsActs; //
    QAction * saveConfig;
    QAction * createNew;
    QAction * openAct;

    QAction * drawPen;
    QAction * penColor;
    QAction * penWidth;
    QAction * brushActive;
    //QRadioButton * alignmentGroup;

    QAction * drawLine;
    QAction * ellipse;
    QAction * square;

    QAction * drawSpecifiSquare;
    QAction * drawSpecifiElipse;
    QAction * lasso;

    QAction * exampleMenu;

    QAction * info;
    QAction * infoQT;
private:
    void createMenu();
    void arratactions();
    QMenu *fileMenu;
    QMenu *penMenu;
    QMenu *shapes;
    QMenu *specifiShapes;
    QMenu *informationMenu;

};
#endif // VIEW_H
