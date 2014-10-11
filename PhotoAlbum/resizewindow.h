#ifndef RESIZEWINDOW_H
#define RESIZEWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QLabel;
class QPixmap;
QT_END_NAMESPACE

namespace Ui {
class ResizeWindow;
}

class ResizeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeWindow(QImage *image, QLabel *imageLabel);//, QWidget *parent = 0);
    ~ResizeWindow();

//private slots:
//    void resetImageSize();

private:
    Ui::ResizeWindow *ui;

    QLabel *resizeImageLabel;
    QImage *resizeImage;
};

#endif // RESIZEWINDOW_H
