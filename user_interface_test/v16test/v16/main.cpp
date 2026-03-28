#include "mainwindow.h"

#include <QApplication>
#include <QPdfView>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
