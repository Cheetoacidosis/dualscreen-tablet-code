#include "mainwindow.h"

#include <QApplication>
#include <QPdfView>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Set default font size for all text
    QFont font = QApplication::font();
    font.setPointSize(30);
    a.setFont(font);
    MainWindow w;
    w.show();
    return a.exec();
}
