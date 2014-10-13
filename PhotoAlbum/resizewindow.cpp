#include "resizewindow.h"
#include "ui_resizewindow.h"

ResizeWindow::ResizeWindow(QImage *image, QLabel *imageLabel) ://, QWidget *parent) :
    //QDialog(parent),
    ui(new Ui::ResizeWindow)
{
    ui->setupUi(this);

    resizeImage = image;
    resizeImageLabel = imageLabel;

    setWindowTitle(tr("Balance"));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(resetImageSize()));

    setWindowTitle(tr("Resize Image"));
}

void ResizeWindow::show()
{
    QDialog::show();
    ui->widthSpinBox->setValue(resizeImage->width());
    ui->heightSpinBox->setValue(resizeImage->height());
}

void ResizeWindow::resetImageSize()
{
//    resizeImage->width() = ui->widthSpinBox->value();
//    resizeImage->height() = ui->heightSpinBox->value();

//    QImage temp = resizeImage->scaled(ui->widthSpinBox->value(), ui->heightSpinBox->value());
//    resizeImageLabel->setPixmap((QPixmap::fromImage(temp)));
    resizeImageLabel->setFixedSize(ui->widthSpinBox->value(), ui->heightSpinBox->value());

    //            ->scaled(ui->widthSpinBox->value(), ui->heightSpinBox->value())));

//    delete ui; //is this. okay. is this okay.
}


ResizeWindow::~ResizeWindow()
{
    delete ui;
}
