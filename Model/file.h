#ifndef FILE_H
#define FILE_H

#include <QList>
#include <QAction>
#include <QMenu>
#include <QObject>

class File:public QObject
{
    Q_OBJECT
public:
    File();
    QMenu *save;
    QAction *load;
    QAction *saveConfig;
    ~File();
};

#endif // FILE_H
