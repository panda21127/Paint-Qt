#include "example.h"

#include <QPainter>
#include <QDebug>

Example::Example(QString threadName):
    name(threadName)
{

}
#if 1
void Example::run(){
    for (int i = 0; i <= 10; i++ ) {
            qDebug() << name << " " << i;
            sleep(1);
        }
}
#endif

#if 0
void Example::run(){
    QImage image = scribbleArea->getImage();
    QPainter painter(&image);
    painter.setPen(QPen(Qt::black,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(10, 30, 150, 30);
    scribbleArea->repaint();
    QThread::sleep(2);
    painter.drawLine(150, 30, 150, 120);
    scribbleArea->repaint();
    QThread::sleep(2);
    painter.drawLine(150, 120, 10, 120);
    scribbleArea->repaint();
    QThread::sleep(2);
    painter.drawLine(10, 120, 10, 30);
    scribbleArea->repaint();
}
#endif
