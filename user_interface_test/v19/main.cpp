#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QPdfView>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");

    // A boolean option with a single name (--tablet-two)
    QCommandLineOption outputSecondTablet("tablet-two", QCoreApplication::translate("main", "Create display file for tablet 2 in /dev/shm/display_data2.bin"));
    parser.addOption(outputSecondTablet);

    // Process the actual command line arguments given by the user
    parser.process(a);

    // Does the user want to output to the second tablet?
    bool secondTablet = parser.isSet(outputSecondTablet);

    //Set default font size for all text
    QFont font = QApplication::font();
    font.setPointSize(26);
    a.setFont(font);
    MainWindow w(nullptr, secondTablet);
    w.show();
    return a.exec();
}
