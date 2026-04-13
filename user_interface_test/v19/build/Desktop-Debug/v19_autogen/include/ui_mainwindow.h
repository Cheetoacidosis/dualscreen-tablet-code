/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtPdfWidgets/QPdfView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *penMed;
    QPushButton *BT_TX;
    QPushButton *Settings;
    QPushButton *Save;
    QPushButton *penLow;
    QPdfView *pdfViewWidget;
    QPushButton *penNone;
    QPushButton *penHigh;
    QPushButton *pageRight;
    QPushButton *Save_As;
    QPushButton *Open;
    QPushButton *BT_RX;
    QPushButton *pageLeft;
    QPushButton *Undo;
    QPushButton *Redo;
    QPushButton *New_File;
    QWidget *page_2;
    QPushButton *Keyboard_Q;
    QPushButton *Keyboard_W;
    QPushButton *Keyboard_E;
    QPushButton *Keyboard_R;
    QPushButton *Keyboard_T;
    QPushButton *Keyboard_Y;
    QPushButton *Keyboard_U;
    QPushButton *Keyboard_I;
    QPushButton *Keyboard_O;
    QPushButton *Keyboard_P;
    QPushButton *Keyboard_A;
    QPushButton *Keyboard_S;
    QPushButton *Keyboard_D;
    QPushButton *Keyboard_F;
    QPushButton *Keyboard_G;
    QPushButton *Keyboard_H;
    QPushButton *Keyboard_J;
    QPushButton *Keyboard_K;
    QPushButton *Keyboard_L;
    QPushButton *Keyboard_Z;
    QPushButton *Keyboard_X;
    QPushButton *Keyboard_C;
    QPushButton *Keyboard_V;
    QPushButton *Keyboard_B;
    QPushButton *Keyboard_N;
    QPushButton *Keyboard_M;
    QPushButton *Keyboard_Dash;
    QPushButton *Keyboard_5;
    QPushButton *Keyboard_1;
    QPushButton *Keyboard_8;
    QPushButton *Keyboard_7;
    QPushButton *Keyboard_0;
    QPushButton *Keyboard_4;
    QPushButton *Keyboard_6;
    QPushButton *Keyboard_3;
    QPushButton *Keyboard_2;
    QPushButton *Keyboard_9;
    QPushButton *Keyboard_Underscore;
    QPushButton *Keyboard_Backspace;
    QTextEdit *textEdit;
    QPushButton *Save_Confirm;
    QPushButton *Cancel;
    QLabel *label;
    QWidget *page_3;
    QListWidget *listWidget;
    QLabel *label_2;
    QPushButton *Cancel_2;
    QWidget *page_4;
    QLabel *label_3;
    QPushButton *Settings_Back;
    QPushButton *Settings_To_Calibrate;
    QPushButton *Settings_To_BT;
    QWidget *page_5;
    QPushButton *Bluetooth_Back;
    QLabel *label_5;
    QWidget *page_6;
    QLabel *label_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(504, 824);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setEnabled(true);
        stackedWidget->setMinimumSize(QSize(480, 800));
        stackedWidget->setMaximumSize(QSize(480, 800));
        page = new QWidget();
        page->setObjectName("page");
        penMed = new QPushButton(page);
        penMed->setObjectName("penMed");
        penMed->setGeometry(QRect(120, 0, 50, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/brush2.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        penMed->setIcon(icon);
        penMed->setIconSize(QSize(40, 40));
        BT_TX = new QPushButton(page);
        BT_TX->setObjectName("BT_TX");
        BT_TX->setGeometry(QRect(410, 730, 50, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/BT_TX.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        BT_TX->setIcon(icon1);
        BT_TX->setIconSize(QSize(40, 40));
        Settings = new QPushButton(page);
        Settings->setObjectName("Settings");
        Settings->setGeometry(QRect(10, 730, 50, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/settings.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Settings->setIcon(icon2);
        Settings->setIconSize(QSize(40, 40));
        Save = new QPushButton(page);
        Save->setObjectName("Save");
        Save->setGeometry(QRect(350, 0, 50, 50));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/save.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Save->setIcon(icon3);
        Save->setIconSize(QSize(40, 40));
        penLow = new QPushButton(page);
        penLow->setObjectName("penLow");
        penLow->setGeometry(QRect(60, 0, 50, 50));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/brush1.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        penLow->setIcon(icon4);
        penLow->setIconSize(QSize(40, 40));
        pdfViewWidget = new QPdfView(page);
        pdfViewWidget->setObjectName("pdfViewWidget");
        pdfViewWidget->setGeometry(QRect(-10, 110, 480, 600));
        pdfViewWidget->setMinimumSize(QSize(480, 600));
        pdfViewWidget->setMaximumSize(QSize(480, 600));
        penNone = new QPushButton(page);
        penNone->setObjectName("penNone");
        penNone->setGeometry(QRect(0, 0, 50, 50));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/none.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        penNone->setIcon(icon5);
        penNone->setIconSize(QSize(40, 40));
        penHigh = new QPushButton(page);
        penHigh->setObjectName("penHigh");
        penHigh->setGeometry(QRect(180, 0, 50, 50));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/brush3.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        penHigh->setIcon(icon6);
        penHigh->setIconSize(QSize(40, 40));
        pageRight = new QPushButton(page);
        pageRight->setObjectName("pageRight");
        pageRight->setGeometry(QRect(240, 730, 50, 50));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/arrow_right.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pageRight->setIcon(icon7);
        pageRight->setIconSize(QSize(40, 40));
        Save_As = new QPushButton(page);
        Save_As->setObjectName("Save_As");
        Save_As->setGeometry(QRect(410, 0, 50, 50));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/save_as.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Save_As->setIcon(icon8);
        Save_As->setIconSize(QSize(40, 40));
        Open = new QPushButton(page);
        Open->setObjectName("Open");
        Open->setGeometry(QRect(350, 50, 50, 50));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/folder.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Open->setIcon(icon9);
        Open->setIconSize(QSize(40, 40));
        BT_RX = new QPushButton(page);
        BT_RX->setObjectName("BT_RX");
        BT_RX->setGeometry(QRect(350, 730, 50, 50));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/BT_RX.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        BT_RX->setIcon(icon10);
        BT_RX->setIconSize(QSize(40, 40));
        pageLeft = new QPushButton(page);
        pageLeft->setObjectName("pageLeft");
        pageLeft->setGeometry(QRect(170, 730, 50, 50));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/arrow_left.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pageLeft->setIcon(icon11);
        pageLeft->setIconSize(QSize(40, 40));
        Undo = new QPushButton(page);
        Undo->setObjectName("Undo");
        Undo->setGeometry(QRect(60, 50, 50, 50));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/undo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Undo->setIcon(icon12);
        Undo->setIconSize(QSize(40, 40));
        Redo = new QPushButton(page);
        Redo->setObjectName("Redo");
        Redo->setGeometry(QRect(120, 50, 50, 50));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/redo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Redo->setIcon(icon13);
        Redo->setIconSize(QSize(40, 40));
        New_File = new QPushButton(page);
        New_File->setObjectName("New_File");
        New_File->setGeometry(QRect(410, 50, 50, 50));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/new_file.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        New_File->setIcon(icon14);
        New_File->setIconSize(QSize(40, 40));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setMinimumSize(QSize(480, 800));
        page_2->setMaximumSize(QSize(480, 800));
        Keyboard_Q = new QPushButton(page_2);
        Keyboard_Q->setObjectName("Keyboard_Q");
        Keyboard_Q->setGeometry(QRect(0, 350, 48, 48));
        Keyboard_W = new QPushButton(page_2);
        Keyboard_W->setObjectName("Keyboard_W");
        Keyboard_W->setGeometry(QRect(48, 350, 48, 48));
        Keyboard_E = new QPushButton(page_2);
        Keyboard_E->setObjectName("Keyboard_E");
        Keyboard_E->setGeometry(QRect(96, 350, 48, 48));
        Keyboard_R = new QPushButton(page_2);
        Keyboard_R->setObjectName("Keyboard_R");
        Keyboard_R->setGeometry(QRect(144, 350, 48, 48));
        Keyboard_T = new QPushButton(page_2);
        Keyboard_T->setObjectName("Keyboard_T");
        Keyboard_T->setGeometry(QRect(192, 350, 48, 48));
        Keyboard_Y = new QPushButton(page_2);
        Keyboard_Y->setObjectName("Keyboard_Y");
        Keyboard_Y->setGeometry(QRect(240, 350, 48, 48));
        Keyboard_U = new QPushButton(page_2);
        Keyboard_U->setObjectName("Keyboard_U");
        Keyboard_U->setGeometry(QRect(288, 350, 48, 48));
        Keyboard_I = new QPushButton(page_2);
        Keyboard_I->setObjectName("Keyboard_I");
        Keyboard_I->setGeometry(QRect(336, 350, 48, 48));
        Keyboard_O = new QPushButton(page_2);
        Keyboard_O->setObjectName("Keyboard_O");
        Keyboard_O->setGeometry(QRect(384, 350, 48, 48));
        Keyboard_P = new QPushButton(page_2);
        Keyboard_P->setObjectName("Keyboard_P");
        Keyboard_P->setGeometry(QRect(432, 350, 48, 48));
        Keyboard_A = new QPushButton(page_2);
        Keyboard_A->setObjectName("Keyboard_A");
        Keyboard_A->setGeometry(QRect(10, 390, 48, 48));
        Keyboard_S = new QPushButton(page_2);
        Keyboard_S->setObjectName("Keyboard_S");
        Keyboard_S->setGeometry(QRect(60, 390, 48, 48));
        Keyboard_D = new QPushButton(page_2);
        Keyboard_D->setObjectName("Keyboard_D");
        Keyboard_D->setGeometry(QRect(110, 390, 48, 48));
        Keyboard_F = new QPushButton(page_2);
        Keyboard_F->setObjectName("Keyboard_F");
        Keyboard_F->setGeometry(QRect(160, 390, 48, 48));
        Keyboard_G = new QPushButton(page_2);
        Keyboard_G->setObjectName("Keyboard_G");
        Keyboard_G->setGeometry(QRect(210, 390, 48, 48));
        Keyboard_H = new QPushButton(page_2);
        Keyboard_H->setObjectName("Keyboard_H");
        Keyboard_H->setGeometry(QRect(260, 390, 48, 48));
        Keyboard_J = new QPushButton(page_2);
        Keyboard_J->setObjectName("Keyboard_J");
        Keyboard_J->setGeometry(QRect(310, 390, 48, 48));
        Keyboard_K = new QPushButton(page_2);
        Keyboard_K->setObjectName("Keyboard_K");
        Keyboard_K->setGeometry(QRect(360, 390, 48, 48));
        Keyboard_L = new QPushButton(page_2);
        Keyboard_L->setObjectName("Keyboard_L");
        Keyboard_L->setGeometry(QRect(410, 390, 48, 48));
        Keyboard_Z = new QPushButton(page_2);
        Keyboard_Z->setObjectName("Keyboard_Z");
        Keyboard_Z->setGeometry(QRect(30, 430, 48, 48));
        Keyboard_X = new QPushButton(page_2);
        Keyboard_X->setObjectName("Keyboard_X");
        Keyboard_X->setGeometry(QRect(80, 430, 48, 48));
        Keyboard_C = new QPushButton(page_2);
        Keyboard_C->setObjectName("Keyboard_C");
        Keyboard_C->setGeometry(QRect(130, 430, 48, 48));
        Keyboard_V = new QPushButton(page_2);
        Keyboard_V->setObjectName("Keyboard_V");
        Keyboard_V->setGeometry(QRect(180, 430, 48, 48));
        Keyboard_B = new QPushButton(page_2);
        Keyboard_B->setObjectName("Keyboard_B");
        Keyboard_B->setGeometry(QRect(230, 430, 48, 48));
        Keyboard_N = new QPushButton(page_2);
        Keyboard_N->setObjectName("Keyboard_N");
        Keyboard_N->setGeometry(QRect(280, 430, 48, 48));
        Keyboard_M = new QPushButton(page_2);
        Keyboard_M->setObjectName("Keyboard_M");
        Keyboard_M->setGeometry(QRect(330, 430, 48, 48));
        Keyboard_Dash = new QPushButton(page_2);
        Keyboard_Dash->setObjectName("Keyboard_Dash");
        Keyboard_Dash->setGeometry(QRect(180, 490, 48, 48));
        Keyboard_5 = new QPushButton(page_2);
        Keyboard_5->setObjectName("Keyboard_5");
        Keyboard_5->setGeometry(QRect(192, 310, 48, 48));
        Keyboard_1 = new QPushButton(page_2);
        Keyboard_1->setObjectName("Keyboard_1");
        Keyboard_1->setGeometry(QRect(0, 310, 48, 48));
        Keyboard_8 = new QPushButton(page_2);
        Keyboard_8->setObjectName("Keyboard_8");
        Keyboard_8->setGeometry(QRect(336, 310, 48, 48));
        Keyboard_7 = new QPushButton(page_2);
        Keyboard_7->setObjectName("Keyboard_7");
        Keyboard_7->setGeometry(QRect(288, 310, 48, 48));
        Keyboard_0 = new QPushButton(page_2);
        Keyboard_0->setObjectName("Keyboard_0");
        Keyboard_0->setGeometry(QRect(432, 310, 48, 48));
        Keyboard_4 = new QPushButton(page_2);
        Keyboard_4->setObjectName("Keyboard_4");
        Keyboard_4->setGeometry(QRect(144, 310, 48, 48));
        Keyboard_6 = new QPushButton(page_2);
        Keyboard_6->setObjectName("Keyboard_6");
        Keyboard_6->setGeometry(QRect(240, 310, 48, 48));
        Keyboard_3 = new QPushButton(page_2);
        Keyboard_3->setObjectName("Keyboard_3");
        Keyboard_3->setGeometry(QRect(96, 310, 48, 48));
        Keyboard_2 = new QPushButton(page_2);
        Keyboard_2->setObjectName("Keyboard_2");
        Keyboard_2->setGeometry(QRect(48, 310, 48, 48));
        Keyboard_9 = new QPushButton(page_2);
        Keyboard_9->setObjectName("Keyboard_9");
        Keyboard_9->setGeometry(QRect(384, 310, 48, 48));
        Keyboard_Underscore = new QPushButton(page_2);
        Keyboard_Underscore->setObjectName("Keyboard_Underscore");
        Keyboard_Underscore->setGeometry(QRect(230, 490, 48, 48));
        Keyboard_Backspace = new QPushButton(page_2);
        Keyboard_Backspace->setObjectName("Keyboard_Backspace");
        Keyboard_Backspace->setGeometry(QRect(350, 490, 91, 48));
        textEdit = new QTextEdit(page_2);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 120, 441, 71));
        Save_Confirm = new QPushButton(page_2);
        Save_Confirm->setObjectName("Save_Confirm");
        Save_Confirm->setGeometry(QRect(290, 590, 91, 48));
        Cancel = new QPushButton(page_2);
        Cancel->setObjectName("Cancel");
        Cancel->setGeometry(QRect(60, 590, 121, 48));
        label = new QLabel(page_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 70, 181, 51));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        listWidget = new QListWidget(page_3);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 90, 441, 641));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 20, 181, 51));
        Cancel_2 = new QPushButton(page_3);
        Cancel_2->setObjectName("Cancel_2");
        Cancel_2->setGeometry(QRect(20, 740, 121, 48));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        label_3 = new QLabel(page_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(190, 10, 181, 81));
        Settings_Back = new QPushButton(page_4);
        Settings_Back->setObjectName("Settings_Back");
        Settings_Back->setGeometry(QRect(10, 750, 121, 48));
        Settings_To_Calibrate = new QPushButton(page_4);
        Settings_To_Calibrate->setObjectName("Settings_To_Calibrate");
        Settings_To_Calibrate->setGeometry(QRect(20, 100, 421, 51));
        Settings_To_BT = new QPushButton(page_4);
        Settings_To_BT->setObjectName("Settings_To_BT");
        Settings_To_BT->setGeometry(QRect(20, 160, 421, 51));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        Bluetooth_Back = new QPushButton(page_5);
        Bluetooth_Back->setObjectName("Bluetooth_Back");
        Bluetooth_Back->setGeometry(QRect(10, 740, 121, 48));
        label_5 = new QLabel(page_5);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 20, 441, 311));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        label_4 = new QLabel(page_6);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(100, 380, 321, 61));
        stackedWidget->addWidget(page_6);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        penLow->setText(QString());
        penNone->setText(QString());
        Save_As->setText(QString());
        Keyboard_Q->setText(QCoreApplication::translate("MainWindow", "Q", nullptr));
        Keyboard_W->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        Keyboard_E->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        Keyboard_R->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        Keyboard_T->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        Keyboard_Y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        Keyboard_U->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        Keyboard_I->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        Keyboard_O->setText(QCoreApplication::translate("MainWindow", "O", nullptr));
        Keyboard_P->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        Keyboard_A->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        Keyboard_S->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        Keyboard_D->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        Keyboard_F->setText(QCoreApplication::translate("MainWindow", "F", nullptr));
        Keyboard_G->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        Keyboard_H->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        Keyboard_J->setText(QCoreApplication::translate("MainWindow", "J", nullptr));
        Keyboard_K->setText(QCoreApplication::translate("MainWindow", "K", nullptr));
        Keyboard_L->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        Keyboard_Z->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        Keyboard_X->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        Keyboard_C->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        Keyboard_V->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        Keyboard_B->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        Keyboard_N->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        Keyboard_M->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        Keyboard_Dash->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        Keyboard_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        Keyboard_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        Keyboard_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        Keyboard_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        Keyboard_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        Keyboard_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        Keyboard_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        Keyboard_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        Keyboard_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        Keyboard_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        Keyboard_Underscore->setText(QCoreApplication::translate("MainWindow", "_", nullptr));
        Keyboard_Backspace->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        Save_Confirm->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Save File As:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Open File:", nullptr));
        Cancel_2->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        Settings_Back->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        Settings_To_Calibrate->setText(QCoreApplication::translate("MainWindow", "Calibrate Screen", nullptr));
        Settings_To_BT->setText(QCoreApplication::translate("MainWindow", "Connect Bluetooth", nullptr));
        Bluetooth_Back->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Bluetooth is enabled...\n"
"Open Bluetooth settings\n"
"on external device.\n"
"Pair to device with name \n"
"\"DS E-Ink Tablet\"", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Screen Calibration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
