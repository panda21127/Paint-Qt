#include "View/view.h"
#include "Delegate/delegate.h"
#include "Model/zoomwidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    //    a = new View();
    //    b = new delegate(&a);
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Paint_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    a.setApplicationName("Zoom widget");
    //ZoomWidget w;
    //w.show();
    View view;
    Delegate *delegate = new Delegate(view);
    view.show();
    return a.exec();
}
