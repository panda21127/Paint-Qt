#include "zoomwidget.h"

#include <QPainter>
#include <QPaintEvent>

ZoomWidget::ZoomWidget()
{

}
void ZoomWidget::mousePressEvent(QMouseEvent *event){
    m_mousePressed = true;
    m_mousePrevPos = event->pos();
}
void ZoomWidget::mouseMoveEvent(QMouseEvent *event){
    if (!m_mousePressed){
            return;
    }
    dMousePos = event->pos() - m_mousePrevPos;
    m_camPos -= dMousePos / m_scale;
    m_mousePrevPos = event->pos();
    repaint();
}

void ZoomWidget::mouseReleaseEvent(QMouseEvent *event){
    m_mousePressed = false;
}

void ZoomWidget::wheelEvent(QWheelEvent *event)
{
    Q_UNUSED(event)
    index = 0;
    QPainter painter(this);
    const qreal scaleCoef = 1.1;
    qreal newScale = event->angleDelta().y() > 0 ? m_scale * scaleCoef :
        m_scale / scaleCoef;
    QPointF dCam = QPointF(event->pos()) * (1. / m_scale - 1. / newScale);
    m_camPos += dCam;
    m_scale = newScale;
    m_mousePrevPos = event->pos();
    repaint();
}
