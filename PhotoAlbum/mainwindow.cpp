#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    this->balanceWidget = new pictureedits(&image, imageLabel);
    this->resizeDialog = new ResizeWindow(&image, imageLabel);
//    this->cropFunction = new CropFunction(&image, imageLabel);

    setWindowTitle(tr("Photo Album"));
    resize(500, 400);

    this->ui->mainToolBar->hide();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
    {
        //QImage image(fileName);
        image = QImage(fileName); //should probably do a thing to check if this is a valid thingy

        if (image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(fileName));
            return;
        }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();
    }
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void MainWindow::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Photo Album"),
            tr("Photo Album description goes here."));
}

void MainWindow::balance()
{
    this->balanceWidget->show();
}

void MainWindow::createActions()
{
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(QIcon(":/images/exit.png"), tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the program"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setStatusTip(tr("Zoom in"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    rotateAct = new QAction(tr("Rotate"), this);
    rotateAct->setShortcut(tr("Ctrl+R"));
    rotateAct->setStatusTip(tr("Rotate Image"));
    rotateAct->setEnabled(false);
    connect(rotateAct, SIGNAL(triggered()), this, SLOT(rotate()));

    resizeAct = new QAction(tr("Resize"), this);
    resizeAct->setShortcut(tr("Ctrl+Z"));
    resizeAct->setStatusTip(tr("Open Resize menu"));
    resizeAct->setEnabled(false);
    connect(resizeAct, SIGNAL(triggered()), this, SLOT(openResize()));

    cropAct = new QAction(tr("Crop"), this);
    cropAct->setShortcut(tr("Ctrl+1"));
    cropAct->setStatusTip(tr("Crop Image"));
    cropAct->setEnabled(false);
    connect(cropAct, SIGNAL(triggered()), this, SLOT(crop()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setStatusTip(tr("Zoom out"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setStatusTip(tr("Return to original size of image"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    fitToWindowAct->setStatusTip("Fit image to window");
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("About this program"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    balanceAct = new QAction(tr("Edit Picture"), this);
    balanceAct->setStatusTip(tr("Open picture edit menu"));
    balanceAct->setEnabled(false);
    connect(balanceAct, SIGNAL(triggered()), this, SLOT(balance()));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    imageMenu = new QMenu(tr("&Image"), this);
    imageMenu->addAction(balanceAct);//should rename
    imageMenu->addAction(rotateAct);
    imageMenu->addAction(resizeAct);
    imageMenu->addAction(cropAct);
    //also rotate, resize, crop.

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(imageMenu);
//    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
//    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
//    fileToolBar->addAction(saveAct);

    viewToolBar = addToolBar(tr("View"));
    viewToolBar->addAction(zoomInAct);
    viewToolBar->addAction(zoomOutAct);
    viewToolBar->addAction(fitToWindowAct);
    viewToolBar->addAction(normalSizeAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::updateActions()
{
    //can probably take out the 'fit to window' things. as soon as we destroy the 'fit to window' thing.
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
    rotateAct->setEnabled(!fitToWindowAct->isChecked());
    resizeAct->setEnabled(!fitToWindowAct->isChecked());
    cropAct->setEnabled(!fitToWindowAct->isChecked());
    balanceAct->setEnabled(!fitToWindowAct->isChecked());
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::rotate()
{
    if(image.isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    qDebug() << "This should eventually rotate the image, but.";

//    QPixmap pix(picImage);

    // create a Qtransform for rotation (can also use for translation and scaling)
//    QTransform *t = new QTransform;

    // rotate pixmap by 45 degrees
//    QPixmap rpix(image.transformed(t->rotate(45)));

    // scale to original image dimensions, retaining aspect ratio
//    QPixmap spix(rpix.scaled(image.width(), image.height(), Qt::KeepAspectRatio));

    // store in label's pixmap
//    imageLabel->setPixmap(spix);

    // more concisely, can collapse the previous three lines into one:
//    picImageLabel->setPixmap(pix.transformed(t->rotate( 45 )).scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));
}

void MainWindow::openResize()
{
    this->resizeDialog->show();
}

void MainWindow::crop()
{
//    this->cropFunction = new CropFunction(&image, imageLabel);
    rubberBand = new QRubberBand( QRubberBand::Rectangle, this );

    validCrop = true;
}

// print button and location of mouse clicks
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(validCrop == true)
    {
    origin = event->pos();

    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
    }
    qDebug() << "mouse press   " << event->button() << " at " << "(" << event->x() << "," << event->y() << ")";
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(validCrop == true)
    {
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
}

void MainWindow::mouseReleaseEvent( QMouseEvent *event )
{
    if(validCrop == true)
    {
    rubberBand->hide();

    qDebug() << "mouse release " << event->button() << " at " << "(" << event->x() << "," << event->y() << ")";

    imageLabel->setPixmap(QPixmap::fromImage(image).copy(QRect(origin, event->pos()).normalized()));
    imageLabel->setGeometry(QRect(origin, event->pos()).normalized());

    delete rubberBand;
    validCrop = false;
    }
}

// print keycode of key presses
//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key() == Qt::Key_Escape)
//        exit(0);
//    qDebug() << "keypress event " << event->key();
//}

MainWindow::~MainWindow()
{
    delete ui;
}
