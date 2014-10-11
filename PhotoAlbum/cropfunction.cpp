#include "cropfunction.h"

CropFunction::CropFunction(QImage *image, QLabel *imageLabel)// : ui(new Ui::CropFunction)
{

    cropImage = image;
    cropImageLabel = imageLabel;

//    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

}

// print button and location of mouse clicks
void CropFunction::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
    qDebug() << "mouse press   " << event->button() << " at " << "(" << event->x() << "," << event->y() << ")";
}

void CropFunction::mouseMoveEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void CropFunction::mouseReleaseEvent( QMouseEvent *event )
{
    rubberBand->hide();

    qDebug() << "mouse release " << event->button() << " at " << "(" << event->x() << "," << event->y() << ")";

    cropImageLabel->setPixmap(QPixmap::fromImage(*cropImage).copy(QRect(origin, event->pos()).normalized()));
    cropImageLabel->setGeometry(QRect(origin, event->pos()).normalized());
}

// print keycode of key presses
void CropFunction::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        exit(0);
    qDebug() << "keypress event " << event->key();
}
