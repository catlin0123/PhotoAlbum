#ifndef PHOTO_H
#define PHOTO_H

#endif // PHOTO_H

#include <QDate>
#include <QString>
using namespace std;

struct Photo
{
    QString FileName;
    QDate  Date;
    QString Location;
    QString Description;
    int Brightness = -1;
    int Contrast = -1;
    int StartCropX = -1;
    int StartCropY = -1;
    int EndCropX = -1;
    int EndCropY = -1;
};
