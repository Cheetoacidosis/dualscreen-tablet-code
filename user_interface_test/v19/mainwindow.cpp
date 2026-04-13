#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mydrawingwidget.h"

#include <QPdfPageSelector>
#include <iostream>
#include <QDir>
#include <QTimer>


//box layout lets us overlay drawing widget on viewer widget
#include <QVBoxLayout>

//macros for pen thicknesses
#define NONE 0
#define LOW 1
#define MEDIUM 2
#define HIGH 3


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , my_document(new QPdfDocument(this))
    , my_pageNavigator(new QPdfPageNavigator(this))


{


    //initialize UI
    ui->setupUi(this);
    //set size and positionf stacked widget
    ui->stackedWidget->setGeometry(0, 0, 480, 800);
    //set fontsize for file saving dialogue
    ui->textEdit->setStyleSheet("font-size: 48pt;");
    //turn off blinking cursor for file saving dialogue
    ui->textEdit->setCursorWidth(0);
    //set menu to main menu
    ui->stackedWidget->setCurrentIndex(0);
    //set default open file directory and folder
    // this->open_document_file = "/Users/ethan/Desktop/Undergrad/Spring 2026/Senior Design/QT/pdf_files/3640_Project_1.pdf";
    // this->pdf_folder_location = "/Users/ethan/Desktop/Undergrad/Spring 2026/Senior Design/QT/pdf_files/";
    this->open_document_file = "/home/pi/pdf_files/demo.pdf";
    this->pdf_folder_location = "home/pi/pdf_files/";

    new_file = false;



    //assign the widget to be connected to the document
    ui->pdfViewWidget->setDocument(my_document);

    //set pdf settings
    ui->pdfViewWidget->setPageMode(QPdfView::PageMode::SinglePage);
    ui->pdfViewWidget->setZoomMode(QPdfView::ZoomMode::FitInView);
    ui->pdfViewWidget->setContentsMargins(0,0,0,0);
    ui->pdfViewWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pdfViewWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set read document location
    my_document->load(this->open_document_file);

    //create pdf annotator widget
    mydrawingwidget *annotator = new mydrawingwidget(ui->pdfViewWidget);
    //create a layout so we can overlay the annotator over the viewer
    QVBoxLayout *layout = new QVBoxLayout(ui->pdfViewWidget);
    //no margins on the layout
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(annotator);
    //set pen default
    annotator->setPenThickness(MEDIUM);


    //Hide submenus
    // ui->testMenuFrame->hide();
    ui->menuFrameFile->hide();
    ui->menuFramePen->hide();




    //when save button is pressed,
    connect(ui->Save, &QPushButton::clicked, this, [this, annotator]() {

        if (new_file) {
            ui->stackedWidget->setCurrentIndex(1);
        }

        else {

        //if you are beyond the document, reset the document for the saving file function
        if (ui->pdfViewWidget->document()==nullptr) {
            ui->pdfViewWidget->setDocument(my_document);
            annotator->saveToPdf(open_document_file, ui->pdfViewWidget);
            ui->pdfViewWidget->setDocument(nullptr);
        } else {

            //save file
            annotator->saveToPdf(open_document_file, ui->pdfViewWidget);
        }

        }
    });


    connect(ui->New_File, &QPushButton::clicked, this, [this, annotator]() {
        new_file = true;
        annotator->clearAnnotations();
        ui->pdfViewWidget->setDocument(nullptr);
    });


    //create a page navigator linked to the widget
    QPdfPageNavigator *navigator = ui->pdfViewWidget->pageNavigator();

    //when page right button is pressed,
    connect(ui->pageRight, &QPushButton::clicked, navigator, [navigator, annotator, this](){
        //advance page up by 1

        //the jump function jumps to a specific page. In our case, it's one page more than the current one
        //the second argument is the location of the page in the viewer, but we just want it defult so {} does that
        //you can specify the zoom as a third argument, but it lets you call it without (??)
        if (navigator->currentPage() < my_document->pageCount() - 1) {
            navigator->jump(navigator->currentPage() + 1, {});
            annotator->advancePageRight();
        }

        //if on or beyond the last page of the document,
        else if (navigator->currentPage() >= my_document->pageCount()-1) {
            //stop viewing pdf, just go to blank page
            ui->pdfViewWidget->setDocument(nullptr);
            annotator->advancePageRight();
        }

    });


    //when page left button is pressed,
    connect(ui->pageLeft, &QPushButton::clicked, navigator, [navigator, annotator, this](){
        //advance page down by 1


        //don't do anything if on page 1
        if (navigator->currentPage() > 0) {
            //if beyond the last page and coming back into the document, enable the pdf viewing again
            if (annotator->pdf_page == my_document->pageCount()) ui->pdfViewWidget->setDocument(my_document);
            //otherwise, just move to the left one page as normal
            else navigator->jump(navigator->currentPage() - 1, {});

            annotator->advancePageLeft();
        }

    });

    //when Save As button is pressed,
    connect(ui->Save_As, &QPushButton::clicked, this, [this]() {
        //switch to the Save As Menu (stacked widget index 1)
        ui->stackedWidget->setCurrentIndex(1);
        ui->textEdit->setFocus();
    });


    connect(ui->penLow, &QPushButton::clicked, this, [this, annotator]() {
        annotator->setPenThickness(LOW);
    });

    connect(ui->penMed, &QPushButton::clicked, this, [this, annotator]() {
        annotator->setPenThickness(MEDIUM);
    });

    connect(ui->penHigh, &QPushButton::clicked, this, [this, annotator]() {
        annotator->setPenThickness(HIGH);
    });

    connect(ui->penNone, &QPushButton::clicked, this, [this, annotator]() {
        annotator->setPenThickness(NONE);
    });




    connect(ui->Undo, &QPushButton::clicked, this, [this, annotator]() {
        annotator->undo();
    });

    connect(ui->Redo, &QPushButton::clicked, this, [this, annotator]() {
        annotator->redo();
    });


    //When Open button is pressed,
    connect(ui->Open, &QPushButton::clicked, this, [this]() {
        //scan the open directory for pdf files
        QDir directory(this->pdf_folder_location);
        QStringList filters;
        filters << "*.pdf";

        ui->listWidget->clear();

        //populate the list widget with the scanned pdf files
        for (const QString &filename :directory.entryList(filters, QDir::Files)) {
            ui->listWidget->addItem(filename);
        }

        //switch to open menu view
        ui->stackedWidget->setCurrentIndex(2);

    });

    //When one of the files is pressed in the Open menu,
    connect(ui->listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        //update the file currently open to the one selected
        QString filename = pdf_folder_location;
        filename += item->text();
        open_document_file = filename;

        //update the pdf viewer with the right document
        my_document->load(open_document_file);

        new_file = false;

        //switch back to pdf view screen
        ui->stackedWidget->setCurrentIndex(0);


    });








    //when Settings button is pressed,
    connect(ui->Settings, &QPushButton::clicked, this, [this]() {
        //go to settings page
        ui->stackedWidget->setCurrentIndex(3);
    });

    //when connect to BT button is pressed,
    connect(ui->Settings_To_BT, &QPushButton::clicked, this, [this]() {
        //go to BT page
        ui->stackedWidget->setCurrentIndex(4);
    });

    //when calibrate button is pressed,
    connect(ui->Settings_To_Calibrate, &QPushButton::clicked, this, [this]() {
        //go to calibrate page
        ui->stackedWidget->setCurrentIndex(5);
    });

    //when Settings Back button is pressed,
    connect(ui->Settings_Back, &QPushButton::clicked, this, [this]() {
        //go to main page
        ui->stackedWidget->setCurrentIndex(0);
    });





    //when BT Settings button is pressed,
    connect(ui->BT_RX, &QPushButton::clicked, this, [this]() {
        //go to settings page
        ui->stackedWidget->setCurrentIndex(4);
    });

    //when Bluetooth Back button is pressed,
    connect(ui->Bluetooth_Back, &QPushButton::clicked, this, [this]() {
        //go to main page
        ui->stackedWidget->setCurrentIndex(0);
    });






    /*
     * All of the following code is for the 'Save As' menu
     */

    //when Cancel button is pressed,
    connect(ui->Cancel, &QPushButton::clicked, this, [this]() {
        //switch out of normal view (stacked widget index 0)
        ui->stackedWidget->setCurrentIndex(0);
    });

    //when Cancel_2 button is pressed,
    connect(ui->Cancel_2, &QPushButton::clicked, this, [this]() {
        //switch out of normal view (stacked widget index 0)
        ui->stackedWidget->setCurrentIndex(0);
    });

    //when Save Confirm button is pressed,
    connect(ui->Save_Confirm, &QPushButton::clicked, this, [this, annotator]() {
        //update file location
        open_document_file = pdf_folder_location;
        open_document_file += ui->textEdit->toPlainText();
        open_document_file += ".pdf";

        if (new_file) {
            annotator->saveToPdfNew(open_document_file);
        } else {

            //if you are beyond the document, reset the document for the saving file function
            if (ui->pdfViewWidget->document()==nullptr) {
                ui->pdfViewWidget->setDocument(my_document);
                annotator->saveToPdf(open_document_file, ui->pdfViewWidget);
                ui->pdfViewWidget->setDocument(nullptr);
            } else {

                //save file
                annotator->saveToPdf(open_document_file, ui->pdfViewWidget);
            }
        }



        //go back to annotation window
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->Keyboard_A, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("A");
    });
    connect(ui->Keyboard_B, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("B");
    });
    connect(ui->Keyboard_C, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("C");
    });
    connect(ui->Keyboard_D, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("D");
    });
    connect(ui->Keyboard_E, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("E");
    });
    connect(ui->Keyboard_F, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("F");
    });
    connect(ui->Keyboard_G, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("G");
    });
    connect(ui->Keyboard_H, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("H");
    });
    connect(ui->Keyboard_I, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("I");
    });
    connect(ui->Keyboard_J, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("J");
    });
    connect(ui->Keyboard_K, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("K");
    });
    connect(ui->Keyboard_L, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("L");
    });
    connect(ui->Keyboard_M, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("M");
    });
    connect(ui->Keyboard_N, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("N");
    });
    connect(ui->Keyboard_O, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("O");
    });
    connect(ui->Keyboard_P, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("P");
    });
    connect(ui->Keyboard_Q, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("Q");
    });
    connect(ui->Keyboard_R, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("R");
    });
    connect(ui->Keyboard_S, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("S");
    });
    connect(ui->Keyboard_T, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("T");
    });
    connect(ui->Keyboard_U, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("U");
    });
    connect(ui->Keyboard_V, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("V");
    });
    connect(ui->Keyboard_W, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("W");
    });
    connect(ui->Keyboard_X, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("X");
    });
    connect(ui->Keyboard_Y, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("Y");
    });
    connect(ui->Keyboard_Z, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("Z");
    });
    connect(ui->Keyboard_1, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("1");
    });
    connect(ui->Keyboard_2, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("2");
    });
    connect(ui->Keyboard_3, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("3");
    });
    connect(ui->Keyboard_4, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("4");
    });
    connect(ui->Keyboard_5, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("5");
    });
    connect(ui->Keyboard_6, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("6");
    });
    connect(ui->Keyboard_7, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("7");
    });
    connect(ui->Keyboard_8, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("8");
    });
    connect(ui->Keyboard_9, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("9");
    });
    connect(ui->Keyboard_0, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("0");
    });
    connect(ui->Keyboard_Dash, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("-");
    });
    connect(ui->Keyboard_Underscore, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("_");
    });

    connect(ui->Keyboard_Backspace, &QPushButton::clicked, this, [this]() {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.deletePreviousChar();
        ui->textEdit->setTextCursor(cursor);
    });



    //Hide & unhide the docks / submenus
    connect(ui->menuFile, &QPushButton::clicked, this, [this]() {
        if (ui->menuFrameFile->isVisible()){
            ui->menuFrameFile->hide();
        } else {
            ui->menuFrameFile->show();
        }
    });
    connect(ui->menuPen, &QPushButton::clicked, this, [this]() {
        if (ui->menuFramePen->isVisible()){
            ui->menuFramePen->hide();
        } else {
            ui->menuFramePen->show();
        }
    });


    //this is the code that pulls the UI data and sends it to the python
    //script at a set frequency
    QTimer *rateGroup = new QTimer(this);
    connect (rateGroup, &QTimer::timeout, this, [this]() {
        //create the right size display
        QImage display(480, 800, QImage::Format_RGB32);
        //file it with a white background
        display.fill(Qt::white);
        //render all of our designed user interface onto the display
        this->render(&display);

        //rotate it
        QTransform transform;
        transform.rotate(90);
        display = display.transformed(transform);
        //convert it to B/W
        display = display.convertToFormat(QImage::Format_Mono, Qt::MonoOnly | Qt::ThresholdDither | Qt::AvoidDither);

        QFile memory_location("/dev/shm/display_data.bin");
        //open the location in memory to write the data
        if (memory_location.open(QIODevice::WriteOnly)) {
            //write the data
            memory_location.write((const char *)display.bits(), display.sizeInBytes());
            memory_location.close();
        }

    });

    rateGroup->start(500);





}

MainWindow::~MainWindow()
{
    delete ui;
    delete my_document;
    delete my_pageNavigator;
}

void MainWindow::on_page_customContextMenuRequested(const QPoint &pos)
{

}

