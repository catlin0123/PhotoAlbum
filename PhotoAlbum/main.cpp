/***************************************************************************
Program # 1 - Photo Album
Course Information
    Authors:
        Caitlin Taggart and Kelsey Bellew
    Due Date:
        10 - 14 - 14
    Professor:
        Dr. Weiss
    Course:
        CSC 421 - M001 - 11am
    Location:
        McLaury 306
Program Information
    Details:
        This is a photo album editor. It allows users to add photos,
        remove photos, edit the description of photos, and edit the look of
        photos through cropping, resizing, rotating, and balancing.  It also
        allows user to move the photos within the album.

        You can save photo albums, create new photo albums, and open photo
        albums.
    Compiling Instructions:
 *****************************************************************************/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //create the main window
    //everything else is done there.
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
