#include "mainwindow.h"

#include <QApplication>
#include <QPdfView>
#include <QFont>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_OFFSCREEN_WIDTH", "800");
    qputenv("QT_QPA_OFFSCREEN_HEIGHT", "480");

    QApplication a(argc, argv);

    //Set default font size for all text
    QFont font = QApplication::font();
    font.setPointSize(30);
    a.setFont(font);

    QGraphicsScene scene(0, 0, 800, 480);

    MainWindow *w = new MainWindow();

    QGraphicsProxyWidget *proxy = scene.addWidget(w);

    proxy->setRotation(90);
    proxy->setPos(800, 0);

    QGraphicsView view(&scene);
    view.resize(800, 480);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFrameShape(QFrame::NoFrame);
    view.show();

    return a.exec();
}