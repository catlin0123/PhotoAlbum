#include "xmlparser.h"
#include <QString>

Parser::Parser()
{

}

vector<Photo> Parser::GetPhotoAlbums(QFile *XMLfile)
{
    XMLfile->open(QIODevice::ReadOnly);
    QDomDocument doc("mydocument");
    doc.setContent(XMLfile);
    XMLfile->close();

    vector<Photo> photoList = vector<Photo>();

    QDomElement docElem = doc.documentElement();
    for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement(); //album
        Photo photo;
        for (QDomNode m = e.firstChild(); !m.isNull(); m = m.nextSibling())
        {
            if (!e.isNull())
            {

                QDomElement f = m.toElement();
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

QString Parser::ConvertList(vector<Photo> photos)
{
    QString string;
    QDate date;
    string += "<album>\n";
    for(unsigned int i = 0; i < photos.size(); i++)
    {
        Photo a = photos[i];
        if (a.FileName != "")
        {
            string += "<photo>\n";
            string += "<filename>" + a.FileName + "</filename>\n";

            if (a.Date != date)
            {
                string += "<date>" + a.Date.toString("MMMM d, yyyy") + "</date>\n";
            }
            if (a.Description != "")
            {
                string += "<description>" + a.Description + "</description>\n";
            }
            if (a.Location != "")
            {
                string +=  "<location>" + a.Location + "</location>\n";
            }
            string +=  "</photo>\n";

        }
    }
    string += "</album>\n";
    return string;
}
