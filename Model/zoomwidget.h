#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QWidget>

class ZoomWidget: public QWidget
{
public:
    ZoomWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    int index;
    QPointF m_camPos {0., 0.};
    qreal m_scale {1.0};
    bool m_mousePressed {false};
    QPoint m_mousePrevPos;
    QPointF dMousePos;
};

#endif // ZOOMWIDGET_H
