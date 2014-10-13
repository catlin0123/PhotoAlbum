/******************************************************************************
File: This file contains the implementation for the Parser class.
 *****************************************************************************/
#include "xmlparser.h"
#include <QString>

/******************************************************************************
Author: Caitlin Taggart
Description: empty contructor for parser class
 *****************************************************************************/
Parser::Parser() //empty contructor
{

}

/******************************************************************************
Author: Caitlin Taggart
Description: Takes an xml file, opens and parses it, and places it in a vector
    of photos.
Parameters: XMLfile - the file to parse
Returns: photoList - the information parsed from the file
 *****************************************************************************/
vector<Photo> Parser::GetPhotoAlbums(QFile *XMLfile)
{
    //open the file to parse
    XMLfile->open(QIODevice::ReadOnly);
    QDomDocument doc("mydocument");
    doc.setContent(XMLfile);
    XMLfile->close();
    //create a list of photos
    vector<Photo> photoList = vector<Photo>();

    //pasrse the document
    QDomElement docElem = doc.documentElement();//album
    for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement(); //photo
        Photo photo;
        for (QDomNode m = e.firstChild(); !m.isNull(); m = m.nextSibling())
        {
            if (!e.isNull())
            {

                QDomElement f = m.toElement();//elements of photo
                if (!f.isNull())
                {
                    QString tag = f.tagName();
                    if (tag == "filename")
                    {
                        photo.FileName = f.text();
                    }
                    else if(tag == "date")
                    {
                        QString text = f.text();
                        photo.Date = QDate::fromString(text, "MMMM d, yyyy");
                    }
                    else if(tag == "location")
                    {
                        photo.Location = f.text();
                    }
                    else if(tag == "description")
                    {
                        photo.Description = f.text();
                    }
                }
            }
        }
        photoList.push_back(photo);
    }

    return photoList;
}

/******************************************************************************
Author: Caitlin Taggart
Description: Takes a vector of photos and converts it to the text that should
    be placed in an xml file.
Parameters: photos - the vector of photos to convert to xml format
Returns: string - the string in xml format to be output to file.
 *****************************************************************************/
QString Parser::ConvertList(vector<Photo> photos)
{
    //create a string for output
    QString string;
    QDate date;
    string += "<album>\n";
    //add each item to the album
    for(unsigned int i = 0; i < photos.size(); i++)
    {
        Photo a = photos[i];
        if (a.FileName != "")//each photo must have a filename
        {
            string += "<photo>\n";
            string += "<filename>" + a.FileName + "</filename>\n";

            if (a.Date != date)//add the date
            {
                string += "<date>" + a.Date.toString("MMMM d, yyyy") + "</date>\n";
            }
            if (a.Description != "")//add the descrption
            {
                string += "<description>" + a.Description + "</description>\n";
            }
            if (a.Location != "")//add the loction
            {
                string +=  "<location>" + a.Location + "</location>\n";
            }
            string +=  "</photo>\n";

        }
    }
    string += "</album>\n";
    return string; //return the xml formatted string
}
