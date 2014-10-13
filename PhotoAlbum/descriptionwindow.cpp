#include "descriptionwindow.h"
#include "ui_descriptionwindow.h"

DescriptionWindow::DescriptionWindow():
    ui(new Ui::DescriptionWindow)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setImageDescription()));

    setWindowTitle(tr("Edit Image Description"));
}

void DescriptionWindow::show()
{
    QDialog::show();
    ui->locationEdit->setText(*location);
    ui->descriptionEdit->setText(*description);
}

DescriptionWindow::~DescriptionWindow()
{
    delete ui;
}

void DescriptionWindow::on_buttonBox_accepted()
{
    *location = ui->locationEdit->text();
    *description = ui->descriptionEdit->text();
    *date = ui->calendarWidget->selectedDate();
    emit descriptionChanged();
}
