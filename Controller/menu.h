#ifndef MENU_H
#define MENU_H

#include <QList>
#include <QMenu>
#include <QWidget>
#include <string>

#include "Model/example.h"
#include "Model/file.h"
#include "Model/information.h"
#include "Model/penedit.h"
#include "Model/scribblearea.h"
#include "Model/Shapes.h"

class Menu
{
public:
    Menu();
    QList<QMenu*> CreateFileMenu();
    QList<QAction*> CreateFileAction();
    QList<QAction*> CreatePenEdit();
    QAction* CreateShape(std::string nameShape);
    //QList<QAction*> CreateExample();
    QList<QAction*> CreateInformation();
private:
    File *file;
    PenEdit *penEdit;
    //Example *example;
    Information *information;
};

#endif // MENU_H
