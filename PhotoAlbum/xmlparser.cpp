#include "xmlparser.h"
#include <QString>

Parser::Parser()
{

}

list<Photo> Parser::GetPhotoAlbums(QFile *XMLfile)
{
    XMLfile->open(QIODevice::ReadOnly);
    QDomDocument doc("mydocument");
    doc.setContent(XMLfile);
    XMLfile->close();

    list<Photo> photoList = list<Photo>();

    QDomElement docElem = doc.documentElement();
    for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement(); //photo
        Photo photo;
        for (QDomNode m = e.firstChild(); !m.isNull(); m = m.nextSibling())
        {
            if (!e.isNull())
            {

                QDomElement f = n.toElement();
                if (!f.isNull())
                {
                    if (f.tagName() == "filename")
                    {
                        photo.FileName = f.text();
                    }
                    else if(f.tagName() == "date")
                    {
                        photo.Date = ConvertTextToDate(f.text());
                    }
                    else if(f.tagName() == "location")
                    {
                        photo.Location = f.text();
                    }
                    else if(f.tagName() == "description")
                    {
                        photo.Description = f.text();
                    }
                    else if(f.tagName() == "brightness")
                    {
                        photo.Brightness = f.text().toInt();
                    }
                    else if(f.tagName() == "contrast")
                    {
                        photo.Contrast = f.text().toInt();
                    }
                    else if(f.tagName() == "x_crop_min")
                    {
                        photo.StartCropX = f.text().toInt();
                    }
                    else if(f.tagName() == "y_crop_min")
                    {
                        photo.StartCropY = f.text().toInt();
                    }
                    else if(f.tagName() == "x_crop_max")
                    {
                        photo.EndCropX = f.text().toInt();
                    }
                    else if(f.tagName() == "y_crop_max")
                    {
                        photo.EndCropY = f.text().toInt();
                    }
                }
            }
        }
        photoList.push_back(photo);
    }

    return photoList;
}

QFile* Parser::ConvertList(list<Photo> *list)
{
    return new QFile();
}

QDate Parser::ConvertTextToDate(QString text)
{
    QDate d = QDate();
    return d;
}
