#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>

class ScribbleArea: public QWidget
{
public:
    ScribbleArea(QWidget *parent = nullptr);

    bool isModified() const {return modified;};
    void setModified(bool mod){ modified = mod;};

    bool isScribbling() const {return scribbling;};
    void setScribbling(bool scribble){ scribbling = scribble;};


    int getPenWidth() const {return myPenWidth;};
    void setPenWidth(int width){ myPenWidth = width;};

    QColor getPenColor() const {return myPenColor;};
    void setPenColor(QColor color){ myPenColor = color;};

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName,const char *fileFormat);
public slots:
    void clearImage();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image,const QSize &newSize);

    QPoint lastPoint;
    QImage image;

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
};

#endif // SCRIBBLEAREA_H
