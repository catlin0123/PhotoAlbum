/******************************************************************************
File: This file contains the implementation for the DescriptionWindow class.
 *****************************************************************************/
#include "descriptionwindow.h"
#include "ui_descriptionwindow.h"


/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Constructor for the Description Window
 *****************************************************************************/
DescriptionWindow::DescriptionWindow():
    ui(new Ui::DescriptionWindow)
{
    ui->setupUi(this);

//    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setImageDescription()));

    setWindowTitle(tr("Edit Image Description"));
}

/******************************************************************************
Author: Caitlin Taggart
Description: shows the dialog and then fills the text with the correct text
    for that photo
 *****************************************************************************/
void DescriptionWindow::show()
{
    QDialog::show();
    ui->locationEdit->setText(*location);
    ui->descriptionEdit->setText(*description);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Stores the location, description, and date when the ok button
    gets pressed. Also emits the description changed signal, so that the
    main window will know that these got changed.
 *****************************************************************************/
void DescriptionWindow::on_buttonBox_accepted()
{
    *location = ui->locationEdit->text();
    *description = ui->descriptionEdit->text();
    *date = ui->calendarWidget->selectedDate();
    emit descriptionChanged();
}

/******************************************************************************
Author: Kelsey Bellew
Description: Destructor for the Description window
 *****************************************************************************/
DescriptionWindow::~DescriptionWindow()
{
    delete ui;
}
