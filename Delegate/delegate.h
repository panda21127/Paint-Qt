#ifndef DELEGATE_H
#define DELEGATE_H

#include "View/view.h"
#include "Model/scribblearea.h"

#include <QWidget>

class Delegate: public QObject
{
    Q_OBJECT
public:
    Delegate(View &viewport);
public slots:
    void open();
    void save();
    void saveConfig();
    void createNew();
    bool saveFile(const QByteArray &fileFormat);
    void about();
    void penColor();
    void penWidth();
private:
    QPoint lastPoint;
    ScribbleArea *scribbleArea;
};

#endif // DELEGATE_H
