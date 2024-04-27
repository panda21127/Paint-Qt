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
#if 0
    ZoomWidget w;
    w.show();
#endif
#if 1
    View view;
    Delegate *delegate = new Delegate();
    delegate->start(view);
    view.show();
#endif
    return a.exec();
}
