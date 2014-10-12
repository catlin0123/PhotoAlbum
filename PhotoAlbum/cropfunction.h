#ifndef CROPFUNCTION_H
#define CROPFUNCTION_H


#include <QMainWindow>
//#include <QtGui>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QtDebug>
#include <QRubberBand>

//#include <QRubberBand>
//#include <QLabel>
//#include <QPixmap>
//#include <QPoint>
//#include <QDebug>

QT_BEGIN_NAMESPACE
class QRubberBand;
class QLabel;
class QPixmap;
QT_END_NAMESPACE

//namespace Ui {
//class CropFunction;
//}

class CropFunction : public QWidget
{
//    Q_OBJECT

public:
    CropFunction(QImage *image, QLabel *imageLabel);
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void keyPressEvent( QKeyEvent *event );

private:
    QRubberBand *rubberBand;
    QPoint origin;

    QLabel *cropImageLabel;
    QImage *cropImage;
};

#endif // CROPFUNCTION_H
