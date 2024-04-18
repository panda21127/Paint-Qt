#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Controller/menu.h"
#include "Model/scribblearea.h"
//#include <QList>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() {};
    void createMenu();
private:
    Menu *menu;
    ScribbleArea *scribbleArea;
    QMenu *fileMenu;
    QMenu *penMenu;
    QMenu *exampleMenu;
    QMenu *informationMenu;
signals:
    void getScribbleArea_signal(ScribbleArea *scribbleArea);
public slots:
    void getScribbleArea_slots();
    void setColor_slots(QColor color);
};
#endif // MAINWINDOW_H
