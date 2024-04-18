#ifndef PENEDIT_H
#define PENEDIT_H

#include <QAction>
#include <QObject>
#include "Model/scribblearea.h"

class PenEdit:public QObject
{
    Q_OBJECT
public:
    PenEdit();
    QAction *colorEdit;
    QAction *widthEdit;
    ~PenEdit();
private slots:
    void penColor();
    void penWidth(ScribbleArea *scribbleArea);
signals:
    void sendColor(QColor color);
};

#endif // PENEDIT_H
