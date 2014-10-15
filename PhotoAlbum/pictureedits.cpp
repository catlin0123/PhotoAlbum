/******************************************************************************
File: This file contains the implementation for the pictureedits class.
 *****************************************************************************/
#include "pictureedits.h"
#include "ui_pictureedits.h"

/******************************************************************************
Author: Kelsey Bellew
Description: Creates everything that is shown in the main window. Connects the
    signals and slots as needed.
Parameters: image - the current image passed in from the main window
            imageLabel - the current image label passed in from the main window
 *****************************************************************************/
pictureedits::pictureedits(QImage *image, QLabel *imageLabel) : ui(new Ui::pictureedits)
{
    brightenPrevVal = 0;
    ui->setupUi(this);

    picImage = image;
    picImageLabel = imageLabel;
    createActions();

    setWindowTitle(tr("Balance"));
}

/******************************************************************************
Author: Kelsey Bellew
Description: Connects the slots that are needed for this class. This
    includes brighten, contrast, edge, gamma, negate, sharpen, and smooth.
 *****************************************************************************/
void pictureedits::createActions()
{
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(brighten(int)));
    connect(ui->contrastButton, SIGNAL(clicked()), this, SLOT(contrast()));
    connect(ui->edgeButton, SIGNAL(clicked()), this, SLOT(edge()));
    connect(ui->gammaButton, SIGNAL(clicked()), this, SLOT(gamma()));
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(negate()));
    connect(ui->sharpenButton, SIGNAL(clicked()), this, SLOT(sharpen()));
    connect(ui->smoothButton, SIGNAL(clicked()), this, SLOT(smooth()));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Brightens or darkens an image, depending on the given value.
Paramaters: i - the current value of the associated widget
 *****************************************************************************/
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

    // brighten the image by 10 intensity levels
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
       picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Applies contrast to an image.
Paramaters: i - the current value of the associated widget
 *****************************************************************************/
void pictureedits::contrast()
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    int contrastVal = 2;

    // contrast stretch image between intensity levels 64 and 192
    for(int x = 0; x < picImage->width(); x++ )
    {
        for (int y = 0; y < picImage->height(); y++)
        {
            QRgb p = picImage->pixel(x, y);
            int r = (qRed(p) - 10) * contrastVal;
            if (r < 0) r = 0; else if (r > 255) r = 255;
            int g = (qGreen(p) - 10) * contrastVal;
            if (g < 0) g = 0; else if (g > 255) g = 255;
            int b = (qBlue(p) - 10) * contrastVal;
            if (b < 0) b = 0; else if (b >255) b = 255;
            picImage->setPixel(x, y, qRgb(r, g, b));
        }
    }

    // store image in label's pixmap
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Applies edge to an image.
 *****************************************************************************/
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

    *picImage = edgeImage;

    // store image in label's pixmap
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Applies gamma to an image.
Paramaters: i - the current value of the associated widget
 *****************************************************************************/
void pictureedits::gamma()
{
    if(picImage->isNull())
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
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Negates an image.
 *****************************************************************************/
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
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Sharpens an image.
Paramaters: i - the current value of the associated widget
 *****************************************************************************/
void pictureedits::sharpen()
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    int val = ui->sharpenSpinBox->value();
    if(val == 0) return;
    val = val/10;

    // sharpen the image prior to display, using
    //  0 -1  0
    // -1  5 -1
    //  0 -1  0
    int sharpenVal = 5;
    QImage sharpImage(*picImage);
    for(int i = 0; i < val; i++)
    {
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
    }

    *picImage = sharpImage;

    // store image in label's pixmap
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Smooths an image.
Paramaters: i - the current value of the associated widget
 *****************************************************************************/
void pictureedits::smooth()
{
    if(picImage->isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

    int val = ui->smoothSpinBox->value();
    if(val == 0) return;
    val = val/10;

    // smooth the image prior to display
    QImage smoothImage(*picImage);

    for(int i = 0; i < val; i++)
    {
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
                smoothImage.setPixel(x, y, qRgb(r / (9), g / (9), b / (9)));
            }
        }
    }

    *picImage = smoothImage;

    // store image in label's pixmap
    picImageLabel->setPixmap(QPixmap::fromImage(*picImage));
}

/******************************************************************************
Author: Kelsey Bellew
Description: The descructor for the picture edits class.
 *****************************************************************************/
pictureedits::~pictureedits()
{
    delete ui;
}
