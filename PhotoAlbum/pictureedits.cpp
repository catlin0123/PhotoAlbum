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

void pictureedits::createActions()
{
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(brighten(int)));
    connect(ui->contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
    connect(ui->edgeButton, SIGNAL(clicked()), this, SLOT(edge()));
    connect(ui->gammaSlider, SIGNAL(valueChanged(int)), this, SLOT(gamma(int)));
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(negate()));
    connect(ui->sharpenSpinBox, SIGNAL(valueChanged(int)), this, SLOT(sharpen(int)));
    connect(ui->smoothSpinBox, SIGNAL(valueChanged(int)), this, SLOT(smooth(int)));
}

//this is wrong somehow.
void pictureedits::brighten(int i)
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    int val;

    //this seems backwards
    if(brightenPrevVal > i) val = -10;
    if(brightenPrevVal < i) val = 10;
    brightenPrevVal = i;

    // brighten the image by 30 intensity levels (25% of intensity range)
    //this goes the right way now? but still does the negate thing horrifically.
       for (int x = 0; x < picImage->width(); x++)
       {
           for (int y = 0; y < picImage->height(); y++)
           {
               QRgb p = picImage->pixel(x, y);
               int r = qRed(p) + val;
               if (r < 0) r = 0; else if (r > 255) r = 255;
               int g = qGreen(p) + val;
               if (g < 0) g = 0; else if (g > 255) g = 255;
               int b = qBlue(p) + val;
               if (b < 0) b = 0; else if (b > 255) b = 255;
               picImage->setPixel(x, y, qRgb(r, g, b));
           }
       }

       // store image in label's pixmap
       //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
       picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

void pictureedits::contrast(int i)
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    double val;
    if(contrastPrevVal > i) val = 1/2; //so. that wasn't right.
    if(contrastPrevVal < i) val = 2;
    contrastPrevVal = i;

    // contrast stretch image between intensity levels 64 and 192
    for(int x = 0; x < picImage->width(); x++ )
    {
        for (int y = 0; y < picImage->height(); y++)
        {
            QRgb p = picImage->pixel(x, y);
            int r = (qRed(p) - 10) * val; //do i have to divide by 2 to get it back ish?
            if (r < 0) r = 0; else if (r > 255) r = 255;
            int g = (qGreen(p) - 10) * val;
            if (g < 0) g = 0; else if (g > 255) g = 255;
            int b = (qBlue(p) - 10) * val;
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
    if(picImage->isNull())
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
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    double val;
    if(gammaPrevVal > i) val = 1.5;
    if(gammaPrevVal < i) val = 2/3; //that also is not right. at. all.
    gammaPrevVal = i;

    // alter image gamma
        double gamma = val;
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
    if(picImage->isNull())
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

void pictureedits::sharpen(int i)
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    // sharpen the image prior to display, using
    //  0 -1  0
    // -1  5 -1
    //  0 -1  0
    int sharpenVal = 5;
    QImage sharpImage(*picImage);
    for(int x = 1; x < picImage->width() - 1; x++)
    {
        for(int y = 1; y < picImage->height() - 1; y++)
        {
            QRgb p = picImage->pixel(x, y);
            int r = sharpenVal * qRed(p);
            int g = sharpenVal * qGreen(p);
            int b = sharpenVal * qBlue(p);
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

    *picImage = sharpImage;

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

//i dont know that this does anything.
void pictureedits::smooth(int i)
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    if(i==0) i = 10;
    i = i/10;

    i = 1;

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
            smoothImage.setPixel(x, y, qRgb(r / (9*i), g / (9*i), b / (9*i)));
        }
    }

    *picImage = smoothImage;

    // store image in label's pixmap
    //setFixedSize(image.size());		// size label to pixmap (may be too large for screen)
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

pictureedits::~pictureedits()
{
    delete ui;
}
