#ifndef PHOTO_H
#define PHOTO_H



#include <QDate>
#include <QString>
using namespace std;

struct Photo
{
    QString FileName = "";
    QDate  Date;
    QString Location = "";
    QString Description = "";
};
#endif // PHOTO_H
