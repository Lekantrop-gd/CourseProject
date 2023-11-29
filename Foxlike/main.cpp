#include "entrywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EntryWindow entryWindow;

    entryWindow.show();
    return a.exec();
}
