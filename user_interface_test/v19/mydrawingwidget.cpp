#include "mydrawingwidget.h"

#include <QPdfDocument>
#include <QPdfWriter>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include <qpdfpagenavigator.h>


//macros for pen thicknesses
#define NONE 0
#define LOW 1
#define MEDIUM 2
#define HIGH 3

#define THICKNESS_SCALE 4

/*
 * A lot of this was pulled from examples online
 *
 *
 *
 *
 */



mydrawingwidget::mydrawingwidget(QWidget *parent)
    : QWidget{parent}
{
    pdf_page = 0;
    annotations_list.resize(1);
    setAttribute(Qt::WA_TranslucentBackground);
}

void mydrawingwidget::setPenThickness(int thickness) {
    this->active_pen_mode = thickness;
}

void mydrawingwidget::undo(void) {
    //check to make sure there exists an annotation to undo
    if (!annotations_list[pdf_page].empty()) {
        //push the last annotation into the undone annotations list
        undone_annotations.push_back(annotations_list[pdf_page].last());
        //pop the last annotation off the stack
        annotations_list[pdf_page].pop_back();

        //update the screen
        current_annotation.clear();
        update();
    }
}

void mydrawingwidget::redo(void) {
    //check to make sure there exists an undone annotation to redo
    if (!undone_annotations.empty()) {
        //push the undone annotation onto the actual annotations list
        annotations_list[pdf_page].push_front(undone_annotations.last());
        //pop the last undone annotation off the stack
        undone_annotations.pop_back();
        //update the screen
        update();
    }
}




void mydrawingwidget::mousePressEvent(QMouseEvent *event){
    //don't create annotation is pen mode is NONE
    if (active_pen_mode != NONE) {

        //when the mouse is pressed, start a new annotation
        current_annotation.clear();
        current_annotation.append(event->position());
        event->accept();
    }
}

void mydrawingwidget::mouseMoveEvent(QMouseEvent *event){
    //don't update annotation if pen mode is NONE
    if (active_pen_mode != NONE) {
        //when the mouse is moved, update the current annotation
        current_annotation.append(event->position());

        update();
    }

}
void mydrawingwidget::mouseReleaseEvent(QMouseEvent *event){
    //don't end annotation is pen mode is NONE
    if (active_pen_mode != NONE) {
        //when the mouse is released, store the current annotation

        //if the annotation was only a single press, turn it into a dot
        if (current_annotation.length() == 1){
            current_annotation.append(event->position() + QPointF(0.10, 0.0));
        }

        //to the list of annotations
        annotation_info new_annotation;
        new_annotation.annotation = current_annotation;
        new_annotation.annotation_thickness = active_pen_mode;

        annotations_list[pdf_page].append(new_annotation);
        update();
    }
}


void mydrawingwidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    //me and all my homies love antialiasing
    painter.setRenderHint(QPainter::Antialiasing);



    //loop through all the saved annotations and display them
    for (const annotation_info &ann: annotations_list[pdf_page]) {
        //set color and pt size
        QPen pen(Qt::black,ann.annotation_thickness*THICKNESS_SCALE);
        painter.setPen(pen);
        painter.drawPolyline(ann.annotation);
    }

    QPen pen(Qt::black,active_pen_mode*THICKNESS_SCALE);
    painter.setPen(pen);
    //display the annotation currently being made
    painter.drawPolyline(current_annotation);

}

void mydrawingwidget::advancePageRight(void) {
    //increase the size of pdf if needed
    if (annotations_list.size() == pdf_page + 1) {
        annotations_list.resize(pdf_page + 2);
    }

    //increment the page counter
    (this->pdf_page)++;

    //clear the undone annotations
    undone_annotations.clear();

    //clear the current annotation so it doesn't appear on the next page
    current_annotation.clear();
    //update the screen to make the old annotations go away
    update();

}

void mydrawingwidget::advancePageLeft(void) {
    //decrement page counter
    (this->pdf_page)--;

    //clear undone annotations
    undone_annotations.clear();
    //clear current annotation
    current_annotation.clear();
    //update screen
    update();
}

void mydrawingwidget::clearAnnotations(void) {
    annotations_list.clear();
    annotations_list.resize(1);
    current_annotation.clear();
    pdf_page=0;
    update();
}

void mydrawingwidget::saveToPdf(const QString &filePath, QPdfView *pdfView) {
    QPdfDocument *my_document = pdfView->document();

    QSizeF pdf_size = my_document->pagePointSize(0);

    QSize viewsize = pdfView->size();

    //Traverse every page of the document before rendering. This prevents my_document->render() from crashing the program
    QPdfPageNavigator *navigator = pdfView->pageNavigator();
    int currentpage = navigator->currentPage();
    for (int i = currentpage; i < my_document->pageCount(); i++){
        navigator->jump(i, {});
    }
    navigator->jump(currentpage, {}); //Return to where we started

    //calculate how much the pdf is scaled in the pdf viewer
    double view_scale = std::min(viewsize.width() / pdf_size.width(), viewsize.height() / pdf_size.height());

    //calculate how much we need to scale the annotations
    double desired_dpi = 300;
    double default_dpi = 72;
    double scaling_factor = desired_dpi/default_dpi;

    //width and height of scaled annotations
    QSize render_size((int)(pdf_size.width() * scaling_factor), (int)(pdf_size.height()*scaling_factor));

    //create the pdf document
    QPdfWriter writer(filePath);
    writer.setResolution(desired_dpi);
    writer.setPageSize(QPageSize(pdf_size, QPageSize::Point));

    //create a new painter, this one linked to the new pdf document we just created
    QPainter finalPainter(&writer);

    int total_pages = std::max<int>(my_document->pageCount(), static_cast<int>(annotations_list.size()));

    //when saving the file, loop through each page in the document
    for (int i=0; i<total_pages; i++) {
        //create an image that is a pixel-to-pixel copy of the pdf document
        QImage page_image;
        QPainter pdf_painter;
        if (i < my_document->pageCount()) {
            page_image = my_document->render(i, render_size);
            pdf_painter.begin(&page_image);
        } else {
            page_image = QImage(render_size, QImage::Format_ARGB32);
            page_image.fill(Qt::white);
            pdf_painter.begin(&page_image);
        }

        //create a painter that loads the pdf image
        pdf_painter.setRenderHint(QPainter::Antialiasing);

        //scale everything right
        pdf_painter.scale(scaling_factor / view_scale, scaling_factor / view_scale);

        //offset the annotations because they don't always come out right
        double x_offset = -8.0;
        double y_offset = -4.0;
        pdf_painter.translate(x_offset, y_offset);

        //loop through all the saved annotations, adding them to the painting
        if (i<annotations_list.size()) {
            for (annotation_info &ann: annotations_list[i]) {
                //set color and pt size
                QPen pen(Qt::black,ann.annotation_thickness*THICKNESS_SCALE);
                pdf_painter.setPen(pen);
                pdf_painter.drawPolyline(ann.annotation);
            }
        }

        pdf_painter.end();

        //draw everything from the previous painter onto this one
        finalPainter.drawImage(0,0,page_image);

        //add the next page, assuming you're not at the end of the document
        if (i < total_pages - 1) {
            writer.newPage();
        }

    }

    finalPainter.end();

    return;
}


void mydrawingwidget::saveToPdfNew(const QString &filePath) {

    QSizeF pdf_size(612,792);

    QSize viewsize=this->size();

    //calculate how much the pdf is scaled in the pdf viewer
    double view_scale = std::min(viewsize.width() / pdf_size.width(), viewsize.height() / pdf_size.height());

    //calculate how much we need to scale the annotations
    double desired_dpi = 300;
    double default_dpi = 72;
    double scaling_factor = desired_dpi/default_dpi;

    //width and height of scaled annotations
    QSize render_size(pdf_size.width() * scaling_factor, pdf_size.height()*scaling_factor);

    //create the pdf document
    QPdfWriter writer(filePath);
    writer.setResolution(desired_dpi);
    writer.setPageSize(QPageSize(pdf_size, QPageSize::Point));

    //create a new painter, this one linked to the new pdf document we just created
    QPainter finalPainter(&writer);

    int total_pages = annotations_list.size();

    //when saving the file, loop through each page in the document
    for (int i=0; i<total_pages; i++) {

        //create an image that is a pixel-to-pixel copy of the pdf document
        QImage page_image;
        QPainter pdf_painter;

        page_image = QImage(render_size, QImage::Format_ARGB32);
        page_image.fill(Qt::white);
        pdf_painter.begin(&page_image);


        //create a painter that loads the pdf image
        pdf_painter.setRenderHint(QPainter::Antialiasing);

        //scale everything right
        pdf_painter.scale(scaling_factor / view_scale, scaling_factor / view_scale);

        //offset the annotations because they don't always come out right
        double x_offset = -8.0;
        double y_offset = -4.0;
        pdf_painter.translate(x_offset, y_offset);

        //loop through all the saved annotations, adding them to the painting
        if (i<annotations_list.size()) {
            for (annotation_info &ann: annotations_list[i]) {
                //set color and pt size
                QPen pen(Qt::black,ann.annotation_thickness*THICKNESS_SCALE);
                pdf_painter.setPen(pen);
                pdf_painter.drawPolyline(ann.annotation);
            }
        }

        pdf_painter.end();

        //draw everything from the previous painter onto this one
        finalPainter.drawImage(0,0,page_image);

        //add the next page, assuming you're not at the end of the document
        if (i < total_pages - 1) {
            writer.newPage();
        }

    }

    finalPainter.end();
}
