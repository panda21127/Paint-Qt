#include "View/view.h"
#include "ui_view.h"

#include <QPainter>
#include <QPaintEvent>
#include <QImageWriter>

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    createMenu();
    setWindowTitle(tr("Paint"));
    resize(800,500);
}

void View::arratactions(){
    foreach(QByteArray format,QImageWriter::supportedImageFormats()){
            QString text = tr("%1...").arg(QString(format).toUpper());
            QAction *action=new QAction(text,this);
            action->setData(format);
            saveAsActs.append(action);
        }
}

void View::createMenu(){
    fileMenu = new QMenu(tr("&File"),this);
    save = new QMenu(tr("Save as ..."),this);
    arratactions();
    foreach(QAction *action,saveAsActs){
            save->addAction(action);
        }

    createNew = new QAction(tr("Create New"),this);

    saveConfig = new QAction(tr("Save Config"),this);
    openAct = new QAction (tr("&Open"),this);
    openAct->setShortcuts(QKeySequence::Open);


    fileMenu->addMenu(save);
    fileMenu->addAction(saveConfig);
    fileMenu->addAction(createNew);
    fileMenu->addSeparator();
    fileMenu->addAction(openAct);

    penMenu = new QMenu(tr("&Pen"),this);
    drawPen = new QAction(tr("Pen"),this);
    penColor = new QAction(tr("Color"),this);
    penWidth = new QAction(tr("Width"),this);
    //brushActive = new QAction(tr("Fill"),this);
    //alignmentGroup = new QRadioButton(tr("Fill"),this);
    brushActive = new QAction(tr("Fill"),this);

    penMenu->addAction(drawPen);
    penMenu->addAction(penColor);
    penMenu->addAction(penWidth);
    penMenu->addAction(brushActive);

    shapes = new QMenu(tr("&Shapes"),this);
    drawLine = new QAction(tr("Line"),this);
    ellipse = new QAction(tr("Ellipse"),this);
    square = new QAction(tr("Square"),this);
    shapes->addAction(drawLine);
    shapes->addAction(ellipse);
    shapes->addAction(square);

    specifiShapes = new QMenu(tr("Specidic &Shapes"),this);
    drawSpecifiElipse = new QAction(tr("Specific Elipse"),this);
    drawSpecifiSquare = new QAction(tr("Specific Square"),this);
    lasso = new QAction(tr("Lasso"),this);
    specifiShapes->addAction(drawSpecifiElipse);
    specifiShapes->addAction(drawSpecifiSquare);
    specifiShapes->addAction(lasso);

    exampleMenu = new QAction(tr("&Example"),this);

    informationMenu = new QMenu(tr("&Information"),this);
    info = new QAction(tr("Info"),this);
    infoQT = new QAction(tr("InfoQT"),this);
    informationMenu->addAction(info);
    informationMenu->addAction(infoQT);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(penMenu);
    menuBar()->addMenu(shapes);
    menuBar()->addMenu(specifiShapes);
    menuBar()->addAction(exampleMenu);
    menuBar()->addMenu(informationMenu);
}

View::~View(){
    delete save;
    foreach(QAction *action,saveAsActs){
           delete action;
        }
    delete saveConfig;
    delete createNew;
    delete openAct;
    delete penColor;
    delete penWidth;
    delete drawLine;
    delete ellipse;
    delete square;
    delete drawSpecifiSquare;
    delete drawSpecifiElipse;
    delete lasso;
    delete info;
    delete infoQT;
    delete fileMenu;
    delete penMenu;
    delete exampleMenu;
    delete shapes;
    delete specifiShapes;
    delete informationMenu;

}

