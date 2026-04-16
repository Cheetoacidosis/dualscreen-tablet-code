#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPdfDocument>
#include <QPdfView>
#include <QPdfPageNavigator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, bool secondTablet = false);
    ~MainWindow();

private slots:
    void on_page_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QPdfDocument *my_document;
    QPdfPageNavigator *my_pageNavigator;
    QString open_document_file;
    QString pdf_folder_location;
    bool new_file;
};
#endif // MAINWINDOW_H
