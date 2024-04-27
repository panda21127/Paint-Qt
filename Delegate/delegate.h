#ifndef DELEGATE_H
#define DELEGATE_H

#include "View/view.h"
#include "Model/scribblearea.h"
#include "Model/example.h"

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

    void drawLine();
    void drawEllipse();
    void drawSquare();

    void drawSpecifiElipse();
    void drawSpecifiSquare();
    void drawLasso();

    void startExample();
private:
    bool saveFile(const QByteArray &fileFormat);
    QPoint lastPoint;
    ScribbleArea *scribbleArea;
};

#endif // DELEGATE_H
