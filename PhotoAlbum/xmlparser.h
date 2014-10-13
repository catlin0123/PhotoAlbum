/******************************************************************************
File: This file contains the header information for the Parser class.
 *****************************************************************************/
#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QtXml>
#include <vector>
#include <QString>
#include "Photo.h"
using namespace std;

class Parser
{
    public:
        Parser();
        vector<Photo> GetPhotoAlbums(QFile *XMLfile);
        QString ConvertList(vector<Photo> list);
};

#endif // XMLPARSER_H
