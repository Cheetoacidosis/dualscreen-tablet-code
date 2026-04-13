/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtPdfWidgets/QPdfView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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
    QWidget *page_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *Keyboard_A;
    QPushButton *Keyboard_S;
    QPushButton *Keyboard_D;
    QPushButton *Keyboard_F;
    QPushButton *Keyboard_G;
    QPushButton *Keyboard_H;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QPushButton *pushButton_25;
    QPushButton *pushButton_26;
    QPushButton *pushButton_27;
    QPushButton *pushButton_28;
    QPushButton *pushButton_29;
    QPushButton *pushButton_30;
    QPushButton *pushButton_31;
    QPushButton *pushButton_32;
    QPushButton *pushButton_33;
    QPushButton *pushButton_34;
    QPushButton *pushButton_35;
    QPushButton *pushButton_36;
    QPushButton *pushButton_37;
    QPushButton *pushButton_38;
    QPushButton *pushButton_39;
    QTextEdit *textEdit;
    QPushButton *Save_Confirm;
    QPushButton *Cancel;
    QWidget *page_3;
    QListWidget *listWidget;

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
        penMed->setGeometry(QRect(120, 10, 57, 32));
        BT_TX = new QPushButton(page);
        BT_TX->setObjectName("BT_TX");
        BT_TX->setGeometry(QRect(380, 720, 71, 32));
        Settings = new QPushButton(page);
        Settings->setObjectName("Settings");
        Settings->setGeometry(QRect(0, 730, 80, 32));
        Save = new QPushButton(page);
        Save->setObjectName("Save");
        Save->setGeometry(QRect(320, 20, 60, 32));
        penLow = new QPushButton(page);
        penLow->setObjectName("penLow");
        penLow->setGeometry(QRect(60, 10, 55, 32));
        pdfViewWidget = new QPdfView(page);
        pdfViewWidget->setObjectName("pdfViewWidget");
        pdfViewWidget->setGeometry(QRect(-12, 75, 480, 600));
        pdfViewWidget->setMinimumSize(QSize(480, 600));
        pdfViewWidget->setMaximumSize(QSize(480, 600));
        penNone = new QPushButton(page);
        penNone->setObjectName("penNone");
        penNone->setGeometry(QRect(-10, 10, 62, 32));
        penHigh = new QPushButton(page);
        penHigh->setObjectName("penHigh");
        penHigh->setGeometry(QRect(180, 10, 58, 32));
        pageRight = new QPushButton(page);
        pageRight->setObjectName("pageRight");
        pageRight->setGeometry(QRect(260, 740, 50, 32));
        Save_As = new QPushButton(page);
        Save_As->setObjectName("Save_As");
        Save_As->setGeometry(QRect(380, 20, 78, 32));
        Open = new QPushButton(page);
        Open->setObjectName("Open");
        Open->setGeometry(QRect(250, 20, 63, 32));
        BT_RX = new QPushButton(page);
        BT_RX->setObjectName("BT_RX");
        BT_RX->setGeometry(QRect(380, 750, 72, 32));
        pageLeft = new QPushButton(page);
        pageLeft->setObjectName("pageLeft");
        pageLeft->setGeometry(QRect(150, 740, 50, 32));
        Undo = new QPushButton(page);
        Undo->setObjectName("Undo");
        Undo->setGeometry(QRect(130, 700, 100, 32));
        Redo = new QPushButton(page);
        Redo->setObjectName("Redo");
        Redo->setGeometry(QRect(250, 700, 100, 32));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setMinimumSize(QSize(480, 800));
        page_2->setMaximumSize(QSize(480, 800));
        pushButton = new QPushButton(page_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 350, 48, 48));
        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(48, 350, 48, 48));
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(96, 350, 48, 48));
        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(144, 350, 48, 48));
        pushButton_5 = new QPushButton(page_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(192, 350, 48, 48));
        pushButton_6 = new QPushButton(page_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(240, 350, 48, 48));
        pushButton_7 = new QPushButton(page_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(288, 350, 48, 48));
        pushButton_8 = new QPushButton(page_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(336, 350, 48, 48));
        pushButton_9 = new QPushButton(page_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(384, 350, 48, 48));
        pushButton_10 = new QPushButton(page_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(432, 350, 48, 48));
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
        pushButton_17 = new QPushButton(page_2);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(310, 390, 48, 48));
        pushButton_18 = new QPushButton(page_2);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(360, 390, 48, 48));
        pushButton_19 = new QPushButton(page_2);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(410, 390, 48, 48));
        pushButton_20 = new QPushButton(page_2);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(30, 430, 48, 48));
        pushButton_21 = new QPushButton(page_2);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(80, 430, 48, 48));
        pushButton_22 = new QPushButton(page_2);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(130, 430, 48, 48));
        pushButton_23 = new QPushButton(page_2);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(180, 430, 48, 48));
        pushButton_24 = new QPushButton(page_2);
        pushButton_24->setObjectName("pushButton_24");
        pushButton_24->setGeometry(QRect(230, 430, 48, 48));
        pushButton_25 = new QPushButton(page_2);
        pushButton_25->setObjectName("pushButton_25");
        pushButton_25->setGeometry(QRect(280, 430, 48, 48));
        pushButton_26 = new QPushButton(page_2);
        pushButton_26->setObjectName("pushButton_26");
        pushButton_26->setGeometry(QRect(330, 430, 48, 48));
        pushButton_27 = new QPushButton(page_2);
        pushButton_27->setObjectName("pushButton_27");
        pushButton_27->setGeometry(QRect(180, 490, 48, 48));
        pushButton_28 = new QPushButton(page_2);
        pushButton_28->setObjectName("pushButton_28");
        pushButton_28->setGeometry(QRect(192, 310, 48, 48));
        pushButton_29 = new QPushButton(page_2);
        pushButton_29->setObjectName("pushButton_29");
        pushButton_29->setGeometry(QRect(0, 310, 48, 48));
        pushButton_30 = new QPushButton(page_2);
        pushButton_30->setObjectName("pushButton_30");
        pushButton_30->setGeometry(QRect(336, 310, 48, 48));
        pushButton_31 = new QPushButton(page_2);
        pushButton_31->setObjectName("pushButton_31");
        pushButton_31->setGeometry(QRect(288, 310, 48, 48));
        pushButton_32 = new QPushButton(page_2);
        pushButton_32->setObjectName("pushButton_32");
        pushButton_32->setGeometry(QRect(432, 310, 48, 48));
        pushButton_33 = new QPushButton(page_2);
        pushButton_33->setObjectName("pushButton_33");
        pushButton_33->setGeometry(QRect(144, 310, 48, 48));
        pushButton_34 = new QPushButton(page_2);
        pushButton_34->setObjectName("pushButton_34");
        pushButton_34->setGeometry(QRect(240, 310, 48, 48));
        pushButton_35 = new QPushButton(page_2);
        pushButton_35->setObjectName("pushButton_35");
        pushButton_35->setGeometry(QRect(96, 310, 48, 48));
        pushButton_36 = new QPushButton(page_2);
        pushButton_36->setObjectName("pushButton_36");
        pushButton_36->setGeometry(QRect(48, 310, 48, 48));
        pushButton_37 = new QPushButton(page_2);
        pushButton_37->setObjectName("pushButton_37");
        pushButton_37->setGeometry(QRect(384, 310, 48, 48));
        pushButton_38 = new QPushButton(page_2);
        pushButton_38->setObjectName("pushButton_38");
        pushButton_38->setGeometry(QRect(230, 490, 48, 48));
        pushButton_39 = new QPushButton(page_2);
        pushButton_39->setObjectName("pushButton_39");
        pushButton_39->setGeometry(QRect(350, 490, 91, 48));
        textEdit = new QTextEdit(page_2);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 60, 441, 71));
        Save_Confirm = new QPushButton(page_2);
        Save_Confirm->setObjectName("Save_Confirm");
        Save_Confirm->setGeometry(QRect(290, 590, 91, 48));
        Cancel = new QPushButton(page_2);
        Cancel->setObjectName("Cancel");
        Cancel->setGeometry(QRect(70, 590, 91, 48));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        listWidget = new QListWidget(page_3);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 30, 441, 741));
        stackedWidget->addWidget(page_3);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        penMed->setText(QCoreApplication::translate("MainWindow", "Med", nullptr));
        BT_TX->setText(QCoreApplication::translate("MainWindow", "TX File", nullptr));
        Settings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        Save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        penLow->setText(QCoreApplication::translate("MainWindow", "Low", nullptr));
        penNone->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        penHigh->setText(QCoreApplication::translate("MainWindow", "High", nullptr));
        pageRight->setText(QCoreApplication::translate("MainWindow", "-->", nullptr));
        Save_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        Open->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        BT_RX->setText(QCoreApplication::translate("MainWindow", "RX File", nullptr));
        pageLeft->setText(QCoreApplication::translate("MainWindow", "<--", nullptr));
        Undo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        Redo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Q", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "O", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        Keyboard_A->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        Keyboard_S->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        Keyboard_D->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        Keyboard_F->setText(QCoreApplication::translate("MainWindow", "F", nullptr));
        Keyboard_G->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        Keyboard_H->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "J", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "K", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        pushButton_24->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        pushButton_25->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        pushButton_26->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        pushButton_27->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_28->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_29->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_30->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pushButton_31->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_32->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_33->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_34->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_35->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_36->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_37->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pushButton_38->setText(QCoreApplication::translate("MainWindow", "_", nullptr));
        pushButton_39->setText(QCoreApplication::translate("MainWindow", "Backspace", nullptr));
        textEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter File Name", nullptr));
        Save_Confirm->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
