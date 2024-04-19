#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class ScribbleArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void createActions();
    void createMenu();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    ScribbleArea *scribbleArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QList<QAction*> saveAsActs;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQTAct;

protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();
    void aboutQt();
};
#endif // MAINWINDOW_H
