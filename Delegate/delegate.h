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
private slots:
    void open();
    void save();
    void saveConfig();
    void createNew();
    void about();
    void penColor();
    void penWidth();
private:
    bool saveFile(const QByteArray &fileFormat);
    QPoint lastPoint;
    ScribbleArea *scribbleArea;
};

#endif // DELEGATE_H
