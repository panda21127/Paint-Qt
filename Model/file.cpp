#include "Model/file.h"
#include <QObject>

File::File()
{
    save = new QMenu(tr("&Save as"));
    load = new  QAction(tr("&Load..."));
    saveConfig = new  QAction(tr("&Save Config..."));
}

File::~File()
{
    delete save;
    delete load;
    delete saveConfig;
}
