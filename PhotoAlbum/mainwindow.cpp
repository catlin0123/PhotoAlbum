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

    setWindowTitle(tr("Photo Album"));
    resize(500, 400);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
    {
        //QImage image(fileName);
        image = QImage(fileName); //should probably do a thing to check if this is a valid thingy
        //um. possibly. um. do a . thing
        //yes. thing. write a function to see if this is valid and then do checks that disallow image changey functions
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
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the program"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setStatusTip(tr("Zoom in"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

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

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


    brightenAct = new QAction(tr("&Brighten"), this);
//    brightenAct->setEnabled(false);
    brightenAct->setStatusTip(tr("Brigten Image"));
    connect(brightenAct, SIGNAL(triggered()), this, SLOT(brighten()));

    contrastAct = new QAction(tr("Contrast"), this);
    contrastAct->setStatusTip(tr("Contrast Image"));
    connect(contrastAct, SIGNAL(triggered()), this, SLOT(contrast()));

    edgeAct = new QAction(tr("Edge"), this);
    edgeAct->setStatusTip(tr("Edge Image (what does that mean even)"));
    connect(edgeAct, SIGNAL(triggered()), this, SLOT(edge()));

    gammaAct = new QAction(tr("&Gamma"), this);
    gammaAct->setStatusTip(tr("Gamma Image ??"));
    connect(gammaAct, SIGNAL(triggered()), this, SLOT(gamma()));

    negateAct = new QAction(tr("Negate"), this);
    negateAct->setStatusTip(tr("Negate Image"));
    connect(negateAct, SIGNAL(triggered()), this, SLOT(negate()));

    rotateAct = new QAction(tr("Rotate"), this);
    rotateAct->setStatusTip(tr("Rotate Image"));
    connect(rotateAct, SIGNAL(triggered()), this, SLOT(rotate()));

    sharpenAct = new QAction(tr("Sharpen"), this);
    sharpenAct->setStatusTip(tr("Sharpen Image"));
    connect(sharpenAct, SIGNAL(triggered()), this, SLOT(sharpen()));

    smoothAct = new QAction(tr("Smooth"), this);
    smoothAct->setStatusTip(tr("Smooth Image"));
    connect(smoothAct, SIGNAL(triggered()), this, SLOT(smooth()));
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

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(brightenAct);
    editMenu->addAction(contrastAct);
    editMenu->addAction(edgeAct);
    editMenu->addAction(gammaAct);
    editMenu->addAction(negateAct);
    editMenu->addAction(rotateAct);
    editMenu->addAction(sharpenAct);
    editMenu->addAction(smoothAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
//    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
//    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(brightenAct);
    editToolBar->addAction(contrastAct);
    editToolBar->addAction(edgeAct);
    editToolBar->addAction(gammaAct);
    editToolBar->addAction(negateAct);
    editToolBar->addAction(rotateAct);
    editToolBar->addAction(sharpenAct);
    editToolBar->addAction(smoothAct);
//    editToolBar->addAction(cutAct);
//    editToolBar->addAction(copyAct);
//    editToolBar->addAction(pasteAct);

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
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
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

void MainWindow::brighten()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // brighten the image by 64 intensity levels (25% of intensity range)
       for (int x = 0; x < image.width(); x++)
       {
           for (int y = 0; y < image.height(); y++)
           {
               QRgb p = image.pixel(x, y);
               int r = qRed(p) + 64;
               if (r > 255) r = 255;
               int g = qGreen(p) + 64;
               if (g > 255) g = 255;
               int b = qBlue(p) + 64;
               if (b > 255) b = 255;
               image.setPixel(x, y, qRgb(r, g, b));
           }
       }

       // store image in label's pixmap
       setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
       imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::contrast()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // contrast stretch image between intensity levels 64 and 192
    for(int x = 0; x < image.width(); x++ )
    {
        for (int y = 0; y < image.height(); y++)
        {
            QRgb p = image.pixel(x, y);
            int r = (qRed(p) - 64) * 2;
            if (r < 0) r = 0; else if (r > 255) r = 255;
            int g = (qGreen(p) - 64) * 2;
            if (g < 0) g = 0; else if (g > 255) g = 255;
            int b = (qBlue(p) - 64) * 2;
            if (b < 0) b = 0; else if (b >255) b = 255;
            image.setPixel(x, y, qRgb(r, g, b));
        }
    }

    // store image in label's pixmap
    setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::edge()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // find edges
    QImage edgeImage(image.width(), image.height(), QImage::Format_RGB32);
    for(int x = 1; x < image.width() - 1; x++)
    {
        for(int y = 1; y < image.height() - 1; y++)
        {
            // pseudo-Prewitt edge magnitude
            int Gx = qGray(image.pixel(x, y + 1)) - qGray(image.pixel( x, y - 1 ));
            int Gy = qGray(image.pixel(x + 1, y)) - qGray(image.pixel( x - 1, y ));
            int e = 3 * sqrt(Gx * Gx + Gy * Gy);
            if (e > 255) e = 255;
            edgeImage.setPixel(x, y, qRgb(e, e, e));
        }
    }

    // store image in label's pixmap
    setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::gamma()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // alter image gamma
        double gamma = 1.5;
        for(int x = 0; x < image.width(); x++)
        {
            for(int y = 0; y < image.height(); y++)
            {
                QRgb p = image.pixel(x, y);
                int r = pow(qRed(p) / 255.0, gamma) * 255 + 0.5;
                int g = pow(qGreen(p) / 255.0, gamma) * 255 + 0.5;
                int b = pow(qBlue(p) / 255.0, gamma) * 255 + 0.5;
                image.setPixel(x, y, qRgb(r, g, b));
            }
        }

    // store image in label's pixmap
    setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::negate()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // could also get image from label's pixmap:
    // QImage image = pixmap()->toImage();

    // negate the image prior to display
    image.invertPixels();

    // store image in label's pixmap
    setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::rotate()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    qDebug() << "This should eventually rotate the image, but.";

//    QPixmap pix(image);

    // create a Qtransform for rotation (can also use for translation and scaling)
//    QTransform *t = new QTransform;

    // rotate pixmap by 45 degrees
//    QPixmap rpix(image.transformed(t->rotate(45)));

    // scale to original image dimensions, retaining aspect ratio
//    QPixmap spix(rpix.scaled(image.width(), image.height(), Qt::KeepAspectRatio));

    // store in label's pixmap
//    imageLabel->setPixmap(spix);

    // more concisely, can collapse the previous three lines into one:
//    imageLabel->setPixmap(pix.transformed(t->rotate( 45 )).scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));
}

void MainWindow::sharpen()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // sharpen the image prior to display, using
    //  0 -1  0
    // -1  5 -1
    //  0 -1  0
    QImage sharpImage(image);
    for(int x = 1; x < image.width() - 1; x++)
    {
        for(int y = 1; y < image.height() - 1; y++)
        {
            QRgb p = image.pixel(x, y);
            int r = 5 * qRed(p);
            int g = 5 * qGreen(p);
            int b = 5 * qBlue(p);
            p = image.pixel(x - 1, y);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);
            p = image.pixel(x + 1, y);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);
            p = image.pixel(x, y - 1);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);
            p = image.pixel(x, y + 1);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);

            if (r < 0) r = 0; else if (r > 255) r = 255;
            if (g < 0) g = 0; else if (g > 255) g = 255;
            if (b < 0) b = 0; else if (b > 255) b = 255;

            sharpImage.setPixel(x, y, qRgb(r, g, b));
        }
    }

    // store image in label's pixmap
    setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::smooth()
{
    if(image.isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // smooth the image prior to display
    QImage smoothImage( image );
    for(int x = 1; x < image.width() - 1; x++)
    {
        for(int y = 1; y < image.height() - 1; y++)
        {
            int r = 0, g = 0, b = 0;
            for(int m = -1; m <= 1; m++)
            {
                for(int n = -1; n <= 1; n++)
                {
                    QRgb p = image.pixel(x + m, y + n);
                    r += qRed(p);
                    g += qGreen(p);
                    b += qBlue(p);
                }
            }
            smoothImage.setPixel(x, y, qRgb(r / 9, g / 9, b / 9));
        }
    }

    // store image in label's pixmap
    setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}
