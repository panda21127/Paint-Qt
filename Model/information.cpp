#include "Model/information.h"
#include <QMessageBox>

#include <QApplication>

Information::Information() {

    info = new QAction(tr("Info ..."));
    connect(info,&QAction::triggered,this,&Information::about);

    infoQt = new QAction(tr("InfoQt ..."));
    connect(infoQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void Information::about(){
    QMessageBox::about(new QWidget,tr("About Scribble"),tr("<p>The <b>Scribble</b> example is awesome </p>"));
}
Information::~Information()
{
    delete info;
    delete infoQt;
}
