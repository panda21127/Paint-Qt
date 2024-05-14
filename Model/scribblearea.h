#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

/*
The class for rendering everything on a widget
*/

#include "Model/Shapes/square.h"

#include <QWidget>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>
#include <QStandardItem>

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

    int getIndex() const {return index;};
    void setIndex(int newIndex){ index = newIndex;};

    QColor getPenColor() const {return myPenColor;};
    void setPenColor(QColor color){ myPenColor = color;};

    QImage getImage() const {return image;};
    void setImage(QImage image_temp){ image = image_temp;};

    void setShape(MyShapes *shape_temp){ shape = shape_temp;};

    void ChangeBrushActive(int brushActive);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName,const char *fileFormat);
    void saveConfigJSON();

    void drawExample();
public slots:
    void clearImage();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void drawObject(MyShapes &shape,const QPoint &endPoint);

    void resizeImage(QImage *image,const QSize &newSize);

    bool loadConfig();

    QJsonDocument doc;
    QJsonParseError docError;
    QString globalPath;
    QPoint lastPoint;
    QPoint tempPoint;
    QImage image;

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;

    int index;
    MyShapes *shape;
};

#endif // SCRIBBLEAREA_H
