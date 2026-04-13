#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mydrawingwidget.h"

#include <QPdfPageSelector>
#include <iostream>
#include <QDir>
#include <QTimer>
#include <QFile>
#include <QImage>
#include <QTransform>

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
    //set menu to default (not file save as menu)
    ui->stackedWidget->setCurrentIndex(0);
    //set default open file directory and folder
    this->open_document_file = "/home/pi/pdf_files/test_pdf.pdf";
    this->pdf_folder_location = "/home/pi/pdf_files/";

    //set background color to white
    this->setStyleSheet("QWidget { background-color: white; }");




    //assign the widget to be connected to the document
    ui->pdfViewWidget->setDocument(my_document);

    //set pdf settings
    ui->pdfViewWidget->setPageMode(QPdfView::PageMode::SinglePage);
    ui->pdfViewWidget->setZoomMode(QPdfView::ZoomMode::FitInView);
    ui->pdfViewWidget->setContentsMargins(0,0,0,0);

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
    annotator->setPenThickness(LOW);


    //when save button is pressed,
    connect(ui->Save, &QPushButton::clicked, this, [this, annotator]() {
        annotator->saveToPdf(open_document_file, ui->pdfViewWidget);
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
    });


    //when page left button is pressed,
    connect(ui->pageLeft, &QPushButton::clicked, navigator, [navigator, annotator, this](){
        //advance page down by 1


        if (navigator->currentPage() > 0) {
            navigator->jump(navigator->currentPage() - 1, {});
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

        //switch back to pdf view screen
        ui->stackedWidget->setCurrentIndex(0);


    });

    connect(ui->Keyboard_A, &QPushButton::clicked, this, [this]() {
        ui->textEdit->insertPlainText("A");
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



    /*
     * All of the following code is for the 'Save As' menu
     */

    //when Back button is pressed,
    connect(ui->Cancel, &QPushButton::clicked, this, [this]() {
        //switch out of normal view (stacked widget index 0)
        ui->stackedWidget->setCurrentIndex(0);
    });

    //when Save Confirm button is pressed,
    connect(ui->Save_Confirm, &QPushButton::clicked, this, [this, annotator]() {
        //update file location
        open_document_file = pdf_folder_location;
        open_document_file += ui->textEdit->toPlainText();
        open_document_file += ".pdf";

        //save file
        annotator->saveToPdf(open_document_file, ui->pdfViewWidget);

        //go back to annotation window
        ui->stackedWidget->setCurrentIndex(0);
    });




    




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