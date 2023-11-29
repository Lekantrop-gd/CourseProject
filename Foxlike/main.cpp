#include "browsewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BrowseWindow window;
    window.show();
    return a.exec();
}
