#include "descriptionwindow.h"
#include "ui_descriptionwindow.h"

DescriptionWindow::DescriptionWindow(QString *description, QString *title): //(QWidget *parent) :
//    QDialog(parent),
    ui(new Ui::DescriptionWindow)
{
    ui->setupUi(this);

    localDescription = description;
    localTitle = title;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setImageDescription()));

    setWindowTitle(tr("Change Image Description"));
}

void DescriptionWindow::setImageDescription()
{
//    localDescription = new QString(ui->descriptionEdit->textChanged()); //I think this is almost correct- this is a pointer though, so it's not quite right.

}

DescriptionWindow::~DescriptionWindow()
{
    delete ui;
}
