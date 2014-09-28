#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QtXml>
#include <list>
#include "Photo.h"

using namespace std;

class Parser
{
    public:
        Parser();
        list<Photo> GetPhotoAlbums(QFile *XMLfile);
        QFile* ConvertList(list<Photo> *list);
        QDate ConvertTextToDate(QString text);
};

#endif // XMLPARSER_H
