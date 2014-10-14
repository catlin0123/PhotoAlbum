/******************************************************************************
File: This file contains the implementation for the ResizeWindow class.
 *****************************************************************************/
#include "resizewindow.h"
#include "ui_resizewindow.h"

/******************************************************************************
Author: Kelsey Bellew
Description: Creates everything that is shown in the main window. Connects the
    signals and slots as needed.
Parameters: image - the current image passed in from the main window
            imageLabel - the current image label passed in from the main window
 *****************************************************************************/
ResizeWindow::ResizeWindow(QImage *image, QLabel *imageLabel) :
    ui(new Ui::ResizeWindow)
{
    ui->setupUi(this);

    resizeImage = image;
    resizeImageLabel = imageLabel;

    setWindowTitle(tr("Balance"));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(resetImageSize()));

    setWindowTitle(tr("Resize Image"));
}

/******************************************************************************
Author: Kelsey Bellew
Description: Override of the show() function to set the text fields with the
    current values of the image.
 *****************************************************************************/
void ResizeWindow::show()
{
    QDialog::show();
    ui->widthSpinBox->setValue(resizeImage->width());
    ui->heightSpinBox->setValue(resizeImage->height());
}

/******************************************************************************
Author: Kelsey Bellew
Description: Resizes an image.
 *****************************************************************************/
void ResizeWindow::resetImageSize()
{
    //set the size of the image label
    resizeImageLabel->setFixedSize(ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

/******************************************************************************
Author: Kelsey Bellew
Description: The descructor for the resize window class.
 *****************************************************************************/
ResizeWindow::~ResizeWindow()
{
    delete ui;
}
