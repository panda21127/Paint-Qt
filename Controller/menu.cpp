#include "Controller/menu.h"
#include <QObject>

Menu::Menu()
{
    file = new File();
    penEdit = new PenEdit();
    printf("One destroy");
    //example = new Example(new QObject);
    information = new Information();
}
QList<QMenu*> Menu::CreateFileMenu(){
    QList<QMenu*> fileMenu;
    fileMenu.append(file->save);
    return fileMenu;
}
QList<QAction*> Menu::CreateFileAction(){
    QList<QAction*> fileMenu;
    fileMenu.append(file->load);
    fileMenu.append(file->saveConfig);
    return fileMenu;
}

QList<QAction*> Menu::CreatePenEdit(){
    QList<QAction*> penEditMenu;
    penEditMenu.append(penEdit->colorEdit);
    QObject::connect(penEdit->colorEdit,SIGNAL(triggered()),penEdit,SLOT(penColor()));

    penEditMenu.append(penEdit->widthEdit);
    return penEditMenu;
}
//TODO
//QAction* Menu::CreateShape(std::string nameShape){
//    return;
//}
/*
QList<QAction*> Menu::CreateExample(){
    QList<QAction*> exampleMenu;
    //exampleMenu.append(example.??); //TODO
    return exampleMenu;
}
*/
QList<QAction*> Menu::CreateInformation(){
    QList<QAction*> informationMenu;
    informationMenu.append(information->info);
    informationMenu.append(information->infoQt);
    return informationMenu;
}
