#include "descriptionwindow.h"
#include "ui_descriptionwindow.h"

DescriptionWindow::DescriptionWindow(QString *description, QString *title)://(QWidget *parent) :
//    QWidget(parent),
    ui(new Ui::DescriptionWindow)
{
    ui->setupUi(this);

    localDescription = description;
    localTitle = title;

    connect(ui->OKButton, SIGNAL(clicked()), this, SLOT(setImageDescription()));

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));

    setWindowTitle(tr("Change Image Description"));
}

void DescriptionWindow::setImageDescription()
{
//    localDescription = ui->descriptionEdit->textChanged(); //please work?

}

void DescriptionWindow::cancelClicked()
{

    this->hide();\
}

DescriptionWindow::~DescriptionWindow()
{
    delete ui;
}
