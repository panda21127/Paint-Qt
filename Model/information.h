#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>
#include <QWidget>
#include <QAction>

class Information:public QObject
{
    Q_OBJECT
public:
    Information();
    QAction * info;
    QAction * infoQt;
    ~Information();
private Q_SLOTS:
    void about();
};

#endif // INFORMATION_H
