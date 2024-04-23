#ifndef VIEW_H
#define VIEW_H

#include "Model/scribblearea.h"

#include <QMainWindow>

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
public:
    QMenu *save;
    QList<QAction*> saveAsActs;
    QAction * saveConfig;
    QAction * createNew;
    QAction * openAct;

    QAction * penColor;
    QAction * penWidth;

    QAction * info;
    QAction * infoQT;
private:
    void createMenu();
    void arratactions();
    QMenu *fileMenu;
    QMenu *penMenu;
    QAction *exampleMenu;
    QMenu *informationMenu;

};
#endif // VIEW_H
