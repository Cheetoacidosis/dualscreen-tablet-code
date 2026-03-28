#ifndef MYDRAWINGWIDGET_H
#define MYDRAWINGWIDGET_H

#include <QWidget>
#include <QPolygonF>
#include <QList>
#include <QPdfDocument>
#include <QPdfView>
#include <vector>


class mydrawingwidget : public QWidget
{
    Q_OBJECT
public:
    explicit mydrawingwidget(QWidget *parent = nullptr);

    void saveToPdf(const QString &filePath, QPdfView *pdfView);
    void saveToPdfNew(const QString &filePath);

    void advancePageRight(void);
    void advancePageLeft(void);

    void setPenThickness(int thickness);

    void undo(void);
    void redo(void);

    //the page currently being annotated
    int pdf_page;

    void clearAnnotations(void);



protected:
    //we need to override these so we can implement
    //our own drawing behavior
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;









private:
    //list of annotations that have been made, prior to writing them to pdf

    struct annotation_info {
        QPolygonF annotation;
        int annotation_thickness;
    };

    std::vector<QList<annotation_info>> annotations_list;

    QList<annotation_info> undone_annotations;

    //the current annotation actively being drawn
    QPolygonF current_annotation;



    int active_pen_mode;


};

#endif // MYDRAWINGWIDGET_H
