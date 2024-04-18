#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea:public QWidget
{
    Q_OBJECT
public:
    ScribbleArea(QWidget *parent = nullptr);
    //bool openImage(const QString &fileName);
    //bool saveImage(const QString &fileName, const char *fileForamt);
    void setPenColor(QColor newColor);
    void setPenWidth(int newWidth);

    bool isModified() const {return modified;}
    QColor GetpenColor() const {return myPenColor;}
    int GetpenWidth() const {return myPenWidth;}

public slots:
    void clearImage();
    //void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image,const QSize &newSize);
    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
};


#endif // SCRIBBLEAREA_H
