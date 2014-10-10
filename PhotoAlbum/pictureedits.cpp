#include "pictureedits.h"
#include "ui_pictureedits.h"

pictureedits::pictureedits(QImage *image, QLabel *imageLabel) : ui(new Ui::pictureedits)
{
    ui->setupUi(this);

    picImage = image;
    picImageLabel = imageLabel;
    createActions();

    setWindowTitle(tr("Balance"));
}

//do we need /any/ of this? (im pretty sure no.)
void pictureedits::createActions()
{
    brightenAct = new QAction(tr("&Brighten"), this);
//    brightenAct->setEnabled(false);
    brightenAct->setStatusTip(tr("Brigten Image"));
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(brighten(int)));

    contrastAct = new QAction(tr("Contrast"), this);
    contrastAct->setStatusTip(tr("Contrast Image"));
    connect(ui->contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));

    edgeAct = new QAction(tr("Edge"), this);
    edgeAct->setStatusTip(tr("Edge Image (what does that mean even)"));
//    connect(edgeAct, SIGNAL(triggered()), this, SLOT(edge());

    gammaAct = new QAction(tr("&Gamma"), this);
    gammaAct->setStatusTip(tr("Gamma Image ??"));
    connect(ui->gammaSlider, SIGNAL(valueChanged(int)), this, SLOT(gamma(int)));

    negateAct = new QAction(tr("Negate"), this);
    negateAct->setStatusTip(tr("Negate Image"));
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(negate()));

    rotateAct = new QAction(tr("Rotate"), this);
    rotateAct->setStatusTip(tr("Rotate Image"));
    connect(rotateAct, SIGNAL(triggered()), this, SLOT(rotate()));

    sharpenAct = new QAction(tr("Sharpen"), this);
    sharpenAct->setStatusTip(tr("Sharpen Image"));
    connect(ui->sharpenSpinBox, SIGNAL(triggered()), this, SLOT(sharpen(int)));

    smoothAct = new QAction(tr("Smooth"), this);
    smoothAct->setStatusTip(tr("Smooth Image"));
    connect(smoothAct, SIGNAL(triggered()), this, SLOT(smooth(int)));
}


void pictureedits::brighten(int i)
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    int val;
    if(i>1) val = 1;
    if(i<0) val = -1;
    if(i==0) val = 0;

    // brighten the image by 64 intensity levels (25% of intensity range)
       for (int x = 0; x < picImage->width(); x++)
       {
           for (int y = 0; y < picImage->height(); y++)
           {
               QRgb p = picImage->pixel(x, y);
               int r = qRed(p) + val;
               if (r > 255) r = 255;
               int g = qGreen(p) + val;
               if (g > 255) g = 255;
               int b = qBlue(p) + val;
               if (b > 255) b = 255;
               picImage->setPixel(x, y, qRgb(r, g, b));
           }
       }

       // store image in label's pixmap
       //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
       picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::contrast(int i)
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // contrast stretch image between intensity levels 64 and 192
    for(int x = 0; x < picImage->width(); x++ )
    {
        for (int y = 0; y < picImage->height(); y++)
        {
            QRgb p = picImage->pixel(x, y);
            int r = (qRed(p) - i) * 2;
            if (r < 0) r = 0; else if (r > 255) r = 255;
            int g = (qGreen(p) - i) * 2;
            if (g < 0) g = 0; else if (g > 255) g = 255;
            int b = (qBlue(p) - i) * 2;
            if (b < 0) b = 0; else if (b >255) b = 255;
            picImage->setPixel(x, y, qRgb(r, g, b));
        }
    }

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::edge()
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // find edges
    QImage edgeImage(picImage->width(), picImage->height(), QImage::Format_RGB32);
    for(int x = 1; x < picImage->width() - 1; x++)
    {
        for(int y = 1; y < picImage->height() - 1; y++)
        {
            // pseudo-Prewitt edge magnitude
            int Gx = qGray(picImage->pixel(x, y + 1)) - qGray(picImage->pixel( x, y - 1 ));
            int Gy = qGray(picImage->pixel(x + 1, y)) - qGray(picImage->pixel( x - 1, y ));
            int e = 3 * sqrt(Gx * Gx + Gy * Gy);
            if (e > 255) e = 255;
            edgeImage.setPixel(x, y, qRgb(e, e, e));
        }
    }

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::gamma(int i)
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // alter image gamma
        double gamma = 1.5;
        for(int x = 0; x < picImage->width(); x++)
        {
            for(int y = 0; y < picImage->height(); y++)
            {
                QRgb p = picImage->pixel(x, y);
                int r = pow(qRed(p) / 255.0, gamma) * 255 + 0.5;
                int g = pow(qGreen(p) / 255.0, gamma) * 255 + 0.5;
                int b = pow(qBlue(p) / 255.0, gamma) * 255 + 0.5;
                picImage->setPixel(x, y, qRgb(r, g, b));
            }
        }

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::negate()
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // could also get image from label's pixmap:
    // QImage image = pixmap()->toImage();

    // negate the image prior to display
    picImage->invertPixels();

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::rotate()
{
    if(picImage->isNull()) //keeping this for now.
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

void pictureedits::sharpen(int i)
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // sharpen the image prior to display, using
    //  0 -1  0
    // -1  5 -1
    //  0 -1  0
    QImage sharpImage(*picImage);
    for(int x = 1; x < picImage->width() - 1; x++)
    {
        for(int y = 1; y < picImage->height() - 1; y++)
        {
            QRgb p = picImage->pixel(x, y);
            int r = 5 * qRed(p);
            int g = 5 * qGreen(p);
            int b = 5 * qBlue(p);
            p = picImage->pixel(x - 1, y);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);
            p = picImage->pixel(x + 1, y);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);
            p = picImage->pixel(x, y - 1);
            r -= qRed(p);
            g -= qGreen(p);
            b -= qBlue(p);
            p = picImage->pixel(x, y + 1);
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
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::smooth(int i)
{
    if(picImage->isNull()) //keeping this for now.
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // smooth the image prior to display
    QImage smoothImage(*picImage);
    for(int x = 1; x < picImage->width() - 1; x++)
    {
        for(int y = 1; y < picImage->height() - 1; y++)
        {
            int r = 0, g = 0, b = 0;
            for(int m = -1; m <= 1; m++)
            {
                for(int n = -1; n <= 1; n++)
                {
                    QRgb p = picImage->pixel(x + m, y + n);
                    r += qRed(p);
                    g += qGreen(p);
                    b += qBlue(p);
                }
            }
            smoothImage.setPixel(x, y, qRgb(r / 9, g / 9, b / 9));
        }
    }

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

pictureedits::~pictureedits()
{
    delete ui;
}
