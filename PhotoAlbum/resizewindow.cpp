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

    //this only gets called at the start. so. so. that's a. problem. hmmmm.
    ui->widthSpinBox->setValue(image->width());
    ui->heightSpinBox->setValue(image->height());

//    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(resetImageSize()));

//    connect(ui->testButton, SIGNAL(clicked()), this, SLOT(resetImageSize()));
}

//ResizeWindow::resetImageSize()
//{
//    resizeImage->width() = ui->widthSpinBox->value();
//    resizeImage->height() = ui->heightSpinBox->value();

//    resizeImageLabel->setPixmap(QPixmap::fromImage(*resizeImage));

////    delete ui; //is this. okay. is this okay.
//}


ResizeWindow::~ResizeWindow()
{
    delete ui;
}