/******************************************************************************
File: This file contains the implementation for the MainWindow class.
 *****************************************************************************/
#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"

/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Creates everything that is shown in the main window. Connects the
    signals and slots as needed.
Parameters: parent - the parent of the MainWindow
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initialize some variabled
    validCrop = false;
    pictureChanged = false;
    albumChanged = false;
    newFile = true;
    currentPicture = 0;

    //set up the label
    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    //set up scrolling
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    //create the decription
    descriptionLabel = new QLabel;
    descriptionLabel->setMinimumHeight(40);
    descriptionLabel->setText("Description:\nLocation:\nDate:");

    //set the cnetral widget
    widget = new QWidget;
    layout = new QVBoxLayout(widget);
    layout->addWidget(scrollArea);
    layout->addWidget(descriptionLabel);
    setCentralWidget(widget);

    //create actions, menus, toolbars, and the status bar
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    //set up dialogs
    this->balanceWidget = new pictureedits(&image, imageLabel);
    this->resizeDialog = new ResizeWindow(&image, imageLabel);
    this->descriptionDialog = new DescriptionWindow();
    connect(descriptionDialog, SIGNAL(descriptionChanged()), this, SLOT(updateDescription()));

    //set title and size
    setWindowTitle(tr("Photo Album"));
    resize(800, 600);

    this->ui->mainToolBar->hide();
}

/******************************************************************************
Author: Caitlin Taggart
Description: Creates a new album. First it checks if the user would like to
    save current changes if there are any and then clears the list of photos
    and sets the image to an empty image. Finally enabled and disables things
    as necessary.
 *****************************************************************************/
void MainWindow::newAlbum()
{
    if (pictureChanged || albumChanged)
    {
        int response = QMessageBox::information(this, tr("Save"),
                tr("This album has been changed. Save changes?"),
                QMessageBox::Ok | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);

        switch (response)
        {
            case QMessageBox::Ok:
                save();
                break;
            case QMessageBox::Discard:
                break;
            case QMessageBox::Cancel:
                return;
                break;
        }
    }
    //create new albums
    album = vector<Photo>();

    //set the image correctly
    image = QImage();
    newFile = true;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.width(), image.height());

    //set the descirption
    setDescription();

    //set enabled as necessary
    enableImageEdits(false);
    deletePhotoAct->setEnabled(false);
    updateMoveEnables();
    saveAct->setEnabled(false);
    saveAsAct->setEnabled(false);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Opens a saved album. First asks the user if he/she would like to
    save changes, then gets a file from the user, parses it, then opens it.
 *****************************************************************************/
void MainWindow::open()
{
    //ask the user if they would like to save changes and then save them
    if (pictureChanged || albumChanged)
    {
        int response = QMessageBox::information(this, tr("Save"),
                tr("This album has been changed. Save changes?"),
                QMessageBox::Ok | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);

        switch (response)
        {
            case QMessageBox::Ok:
                save();
                break;
            case QMessageBox::Discard:
                break;
            case QMessageBox::Cancel:
                return; //don't open a file just return
                break;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("XML files (*.xml)"));
    if (!fileName.isEmpty())
    {
        //set the filename
        filename = fileName;
        newFile = false;

        //parse the file
        QFile* file = new QFile(filename);
        Parser parse;
        currentPicture = 0;
        album = parse.GetPhotoAlbums(file);

        //set the current image and set enables as needed
        if (album.size() != 0)
        {
            image = QImage(album[0].FileName);
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->resize(image.width(), image.height());
            enableImageEdits(true);
            deletePhotoAct->setEnabled(true);
            editDescriptionAct->setEnabled(true);
        }
        else
        {
            enableImageEdits(false);
            deletePhotoAct->setEnabled(false);
            editDescriptionAct->setEnabled(false);
        }
        if (image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(filename));
            return;
        }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;
        updateActions();
    }
    //update enabled as needed
    updateMoveEnables();
    setDescription();
    saveAct->setEnabled(false);
    saveAsAct->setEnabled(false);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Saves an xml file if it has a filename, otherwise calls save as
    which will prompt the user to get a filename.
 *****************************************************************************/
void MainWindow::save()
{
    if (newFile)
    {
        //since it doesn't have a file name use save as
        saveAs();
    }
    else
    {
        //saves the picture if needed
        if (pictureChanged)
        {
            image.save(album[currentPicture].FileName);
        }
        //intialize the file.
        QFile file;
        newFile = false;
        file.setFileName(filename);
        file.open(QIODevice::ReadWrite);

        //parse the file
        Parser parse;
        QString string = parse.ConvertList(album);
        QTextStream stream(&file);

        //output the file
        stream << string;
        file.close();
        albumChanged = false;
    }
}

/******************************************************************************
Author: Caitlin Taggart
Description: Saves the picture if needed, and then saves the xml file format
    of the album.
 *****************************************************************************/
void MainWindow::saveAs()
{
    if (pictureChanged)
    {
        //save the picture
        image.save(album[currentPicture].FileName);
    }
    //save the album
    QFile file;
    filename = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("XML files (*.xml)"));
    newFile = false;
    file.setFileName(filename);
    file.open(QIODevice::ReadWrite);

    //parse the album to get the xml format
    Parser parse;
    QString string = parse.ConvertList(album);

    //output it to file
    QTextStream stream(&file);
    stream << string;
    file.close();
    albumChanged = false;
}

/******************************************************************************
Author: Caitlin Taggart
Description: If there are changes to the album save ask the user if they want
    to save changes, and then exit the program. If not just exit.
 *****************************************************************************/
void MainWindow::close()
{
    if (albumChanged)//ask user to save changes
    {
        int response = QMessageBox::information(this, tr("Save"),
                tr("Save changes before closing?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);

        switch (response)
        {
            case QMessageBox::Save :
            {
                save();
                //quit the program
                QApplication::quit();
                break;
            }
            case QMessageBox::Discard :
            {
                //quit the program
                QApplication::quit();
                break;
            }
            case QMessageBox::Cancel :
                break;
            default:
                break;
        }

    }
    else
    {
        //quit program
        QApplication::quit();
    }
}

/******************************************************************************
Author: Caitlin Taggart
Description: Adds a photo to the back of the photo album. Does so by prompting
    the user for the photo they would like to add and then opens it and sets
    the image to be the last image.
 *****************************************************************************/
void MainWindow::addPhoto()
{
    Photo photo;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName != "")
    {
        //set the image
        image = QImage(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.width(), image.height());

        //since a photo was added image edits is possible
        enableImageEdits(true);
        photo.FileName = fileName;

        //add photo to end of list and update current picture
        album.push_back(photo);
        currentPicture = album.size() - 1;
        albumChanged = true;

        //set the description
        setDescription();
    }
    if (album.size() != 0)
    {
        //enable some of the things
        deletePhotoAct->setEnabled(true);
        editDescriptionAct->setEnabled(true);
    }
    //set enables as needed
    updateMoveEnables();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Deletes the current photo from the album, after prompting the user
    if they want to.
 *****************************************************************************/
void MainWindow::deletePhoto()
{
    if (album.size() != 0)
    {
        //prompt the user to delete the phtot
        int response = QMessageBox::information(this, tr("Delete"),
                tr("Delete current photo from album?"),
                QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

        switch (response)
        {
            case QMessageBox::Ok:
                //delete photo from list
                for (unsigned int i = currentPicture; i + 1 < album.size(); i++)
                {
                    album[i + 1] = album[i];
                }
                album.pop_back();

                //open next photo for viewing
                if (currentPicture == album.size())
                {
                    currentPicture = album.size() - 1;
                }
                if (album.size() != 0 )
                {
                    //set the next image in the list
                    image = QImage(album[currentPicture].FileName);
                    imageLabel->setPixmap(QPixmap::fromImage(image));
                    imageLabel->resize(image.width(), image.height());
                }
                else
                {
                    //empty album set to empty picture
                    image = QImage();
                    imageLabel->setPixmap(QPixmap::fromImage(image));
                    imageLabel->resize(image.width(),image.height());
                    enableImageEdits(false);
                }
                albumChanged = true;
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
    if (album.size() == 0)
    {
        //check enables
        deletePhotoAct->setEnabled(false);
        editDescriptionAct->setEnabled(false);
    }
    //enable as necessary
    updateMoveEnables();
    setDescription();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Brings up the dialog box prefilled with the description
    information already within it.
 *****************************************************************************/
void MainWindow::editDescription()
{
    //set the information to be prefilled
    descriptionDialog->location = &album[currentPicture].Location;
    descriptionDialog->description = &album[currentPicture].Description;
    descriptionDialog->date = &album[currentPicture].Date;
    //show dialog
    descriptionDialog->show();
}

/******************************************************************************
Author: Caitlin Taggart
Description: Gets the information from the dialog box, and then sets the
    description label to have that information within it.
 *****************************************************************************/
void MainWindow::updateDescription()
{
    //get information from the dialog box
    album[currentPicture].Description = *(descriptionDialog->description);
    album[currentPicture].Location = *(descriptionDialog->location);
    album[currentPicture].Date = *(descriptionDialog->date);
    albumChanged = true;

    //set the label of the current window to have appropriate information
    setDescription();

    //allow for saving
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

/******************************************************************************
Author: Caitlin Taggart
Description: moves to the next photo within the album after asking to save the
    photo if there were changes.
 *****************************************************************************/
void MainWindow::nextPhoto()
{
    //can only move to the next photo if not at the end
    if (currentPicture != album.size() - 1 && album.size() != 0)
    {
        if (pictureChanged) //ask the user to save the file
        {
            int response = QMessageBox::information(this, tr("Save"),
                    tr("Save changes to photo?"),
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);

            switch (response)
            {
                case QMessageBox::Save :
                {
                    //save the picture
                    image.save(album[currentPicture].FileName);
                    break;
                }
                case QMessageBox::Discard :
                    break;
                case QMessageBox::Cancel :
                    return;
                    break;
                default:
                    break;
            }
        }
        //move to the next picture
        currentPicture = currentPicture + 1;
        image = QImage(album[currentPicture].FileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.width(), image.height());
        pictureChanged = false;
    }
    //update enables
    updateMoveEnables();
    setDescription();
}

/******************************************************************************
Author: Caitlin Taggart
Description: Moves to the previous photo within the album after asking to save
    the photo if there were changes
 *****************************************************************************/
void MainWindow::previousPhoto()
{
    if (currentPicture != 0)
    {
        if (pictureChanged)
        {
            //ask to save the photo
            int response = QMessageBox::information(this, tr("Save"),
                    tr("Save changes to photo?"),
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);

            switch (response)
            {
                case QMessageBox::Save :
                {
                    //save the the picture
                    image.save(album[currentPicture].FileName);
                    break;
                }
                case QMessageBox::Discard :
                    break;
                case QMessageBox::Cancel :
                    return;
                    break;
                default:
                    break;
            }
        }
        //move back an image.
        currentPicture = currentPicture - 1;
        image = QImage(album[currentPicture].FileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.width(), image.height());
        pictureChanged = false;
    }
    //update enables as necessary
    updateMoveEnables();
    setDescription();
}

/******************************************************************************
Author: Caitlin Taggart
Description: Moves the photo forward in the album. Updates enables as needed.
 *****************************************************************************/
void MainWindow::moveForward()
{
    //make sure we don't step off the end of the vector
    if (currentPicture + 1 < album.size())
    {
        //swap the photos
        Photo temp = album[currentPicture];
        album[currentPicture] = album[currentPicture + 1];
        album[currentPicture + 1] = temp;
        albumChanged = true;
        currentPicture = currentPicture + 1;
    }
    //update enables
    updateMoveEnables();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Moves the photo backward in the album. Updates enables as needed.
 *****************************************************************************/
void MainWindow::moveBackward()
{
    //check that we don't step off the end of the vector
    if ((currentPicture - 1) >= 0 && album.size() != 0)
    {
        Photo temp = album[currentPicture];
        album[currentPicture] = album[currentPicture - 1];
        album[currentPicture - 1] = temp;
        albumChanged = true;
        currentPicture = currentPicture - 1;
    }
    //update enables
    updateMoveEnables();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

/******************************************************************************
Author: Caitlin Taggart
Description: Gives a basic about for the the program.
 *****************************************************************************/
void MainWindow::about()
{
    QString str;
    str = "Photo Album allows you to add, delete, edit, and add a description to photos.";
    QMessageBox::about(this, tr("About Photo Album"), str);
}

/******************************************************************************
Author: Kelsey Bellew
Description: Opens the balance window.
 *****************************************************************************/
void MainWindow::balance()
{
    //show balance window
    this->balanceWidget->show();

    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);

    pictureChanged = true;
}

/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Creates the different actions needed for the program. This
    includes new, open, save, save as, exit, add photo, delete photo, edit
    description, next photo, previous photo, move forward, move backward,
    rotate, resize, crop, about, and balance actions. For each it sets the
    icon if there is one, the text, keyboard short cuts, enables and disables
    them initially, and connects them to signals as needed.
 *****************************************************************************/
void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/icon/images/new.png"), tr("&New..."), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new album"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newAlbum()));

    openAct = new QAction(QIcon(":/icon/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/icon/images/save.png"), tr("&Save..."), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save album"));
    saveAct->setEnabled(false);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction("Save&As...", this);
    saveAsAct->setShortcut(tr("Ctrl+Alt+S"));
    saveAsAct->setStatusTip(tr("Save album as"));
    saveAsAct->setEnabled(false);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(QIcon(":/icon/images/exit.png"), tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the program"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    addPhotoAct = new QAction(QIcon(":/icon/images/add-new.png"), tr("&Add Photo"), this);
    addPhotoAct->setShortcut(tr("Ctrl+A"));
    addPhotoAct->setStatusTip(tr("Add photo to album"));
    connect(addPhotoAct, SIGNAL(triggered()), this, SLOT(addPhoto()));

    deletePhotoAct = new QAction(QIcon(":/icon/images/delete.png"), tr("&Delete Photo"), this);
    deletePhotoAct->setShortcut(tr("Ctrl+D"));
    deletePhotoAct->setStatusTip(tr("Delete photo from album"));
    deletePhotoAct->setEnabled(false);
    connect(deletePhotoAct, SIGNAL(triggered()), this, SLOT(deletePhoto()));

    editDescriptionAct = new QAction(tr("&Edit Description"), this);
    editDescriptionAct->setShortcut(tr("Ctrl+E"));
    editDescriptionAct->setStatusTip(tr("Edit photo description"));
    editDescriptionAct->setEnabled(false);
    connect(editDescriptionAct, SIGNAL(triggered()), this, SLOT(editDescription()));

    nextPhotoAct = new QAction(QIcon(":/icon/images/arrow-right.png"), tr("&Next Photo"), this);
    nextPhotoAct->setShortcut(tr("Ctrl+X"));
    nextPhotoAct->setStatusTip(tr("View next photo"));
    nextPhotoAct->setEnabled(false);
    connect(nextPhotoAct, SIGNAL(triggered()), this, SLOT(nextPhoto()));

    previousPhotoAct = new QAction(QIcon(":/icon/images/arrow-left.png"), tr("&Previous Photo"), this);
    previousPhotoAct->setShortcut(tr("Ctrl+P"));
    previousPhotoAct->setStatusTip(tr("View previous photo"));
    previousPhotoAct->setEnabled(false);
    connect(previousPhotoAct, SIGNAL(triggered()), this, SLOT(previousPhoto()));

    moveForwardAct = new QAction(QIcon(":/icon/images/arrow-down.png"), tr("&Move Photo Forward"), this);
    moveForwardAct->setShortcut(tr("Ctrl+M"));
    moveForwardAct->setStatusTip(tr("Move photo forward in album"));
    moveForwardAct->setEnabled(false);
    connect(moveForwardAct, SIGNAL(triggered()), this, SLOT(moveForward()));

    moveBackwardAct = new QAction(QIcon(":/icon/images/arrow-up.png"), tr("&Move Photo Backward"), this);
    moveBackwardAct->setShortcut(tr("Ctrl+B"));
    moveBackwardAct->setStatusTip(tr("Move photo backward in album"));
    moveBackwardAct->setEnabled(false);
    connect(moveBackwardAct, SIGNAL(triggered()), this, SLOT(moveBackward()));

    rotateAct = new QAction(tr("Rotate"), this);
    rotateAct->setShortcut(tr("Ctrl+R"));
    rotateAct->setStatusTip(tr("Rotate Image"));
    rotateAct->setEnabled(false);
    connect(rotateAct, SIGNAL(triggered()), this, SLOT(rotate()));

    resizeAct = new QAction(tr("Resize"), this);
    resizeAct->setShortcut(tr("Ctrl+Z"));
    resizeAct->setStatusTip(tr("Open Resize menu"));
    resizeAct->setEnabled(false);
    connect(resizeAct, SIGNAL(triggered()), this, SLOT(openResize()));

    cropAct = new QAction(tr("Crop"), this);
    cropAct->setShortcut(tr("Ctrl+C"));
    cropAct->setStatusTip(tr("Crop Image"));
    cropAct->setEnabled(false);
    connect(cropAct, SIGNAL(triggered()), this, SLOT(crop()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("About this program"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    balanceAct = new QAction(tr("Edit Picture"), this);
    balanceAct->setStatusTip(tr("Open picture edit menu"));
    balanceAct->setEnabled(false);
    connect(balanceAct, SIGNAL(triggered()), this, SLOT(balance()));
}

/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Creates the menus include file, edit, image, and help menus.
    For each of these it add appropriate actions.
 *****************************************************************************/
void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(addPhotoAct);
    editMenu->addAction(deletePhotoAct);
    editMenu->addSeparator();
    editMenu->addAction(editDescriptionAct);
    editMenu->addSeparator();
    editMenu->addAction(nextPhotoAct);
    editMenu->addAction(previousPhotoAct);
    editMenu->addAction(moveForwardAct);
    editMenu->addAction(moveBackwardAct);


    imageMenu = new QMenu(tr("&Image"), this);
    imageMenu->addAction(balanceAct);
    imageMenu->addAction(rotateAct);
    imageMenu->addAction(resizeAct);
    imageMenu->addAction(cropAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(imageMenu);
    menuBar()->addMenu(helpMenu);
}

/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Creates the toolbars including file, edit, and help menus.
    For each of these it add appropriate actions.
 *****************************************************************************/
void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(exitAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(addPhotoAct);
    editToolBar->addAction(deletePhotoAct);
    //editToolBar->addAction(editDescriptionAct);
    editToolBar->addSeparator();
    editToolBar->addAction(previousPhotoAct);
    editToolBar->addAction(nextPhotoAct);
    editToolBar->addAction(moveBackwardAct);
    editToolBar->addAction(moveForwardAct);

}

/******************************************************************************
Author: Kelsey Bellew
Description: Creates the Status Bar and sets an initial message.
 *****************************************************************************/
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

/******************************************************************************
Author: Kelsey Bellew
Description: Updates image changing operations and sets them to enabled.
 *****************************************************************************/
void MainWindow::updateActions()
{
    rotateAct->setEnabled(true);
    resizeAct->setEnabled(true);
    cropAct->setEnabled(true);
    balanceAct->setEnabled(true);
}


/******************************************************************************
Author: Digia Plc, edited by Kelsey Bellew
Description: Adjusts the Scroll Bar.
 *****************************************************************************/
void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

/******************************************************************************
Author: Kelsey Bellew
Description: Rotates the image 90 degrees right and updates the image label.
 *****************************************************************************/
void MainWindow::rotate()
{
    if(image.isNull())
    {
        qDebug() << "image does not exist";
        exit(-2);
    }

    //get a pixmap to rotate
    QPixmap pix(*imageLabel->pixmap());
    QMatrix matrix;
    matrix.rotate(90);
    pix = pix.transformed(matrix);

    //find current width and height
    int w = image.width();
    int h = image.height();

    //rotate current image
    QTransform *t = new QTransform;
    image = image.transformed(t->rotate(90)).scaled(h, w, Qt::KeepAspectRatio);

    //set imageLabel to the rotated pixmap with the correct dimesions.
    imageLabel->setPixmap(pix.scaled(h, w, Qt::KeepAspectRatio));
    imageLabel->setFixedSize(h, w);

    pictureChanged = true;
}


/******************************************************************************
Author: Kelsey Bellew
Description: Opens the resize window.
 *****************************************************************************/
void MainWindow::openResize()
{
    //show resize window
    resizeDialog->show();

    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);

    pictureChanged = true;
}




/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Instantiates a rubber band and sets validCrop to true.
 *****************************************************************************/
void MainWindow::crop()
{
    //get a new instance of a rubberband and tell the program that we are cropping
    rubberBand = new QRubberBand( QRubberBand::Rectangle, this );
    validCrop = true;
}


/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Grabs all mouse events, and if the program is in a valid cropping
    state, sets up the rubber band.
Paramaters: event - the current mouse event
 *****************************************************************************/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //set the origin and set up the rubberband, if rubberband exists
    if(validCrop == true)
    {
        origin = event->pos();

        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
    }
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: When the rubber band is being moved around, this function sets
    the geometry of the rubber band.
Paramaters: event - the current mouse event
 *****************************************************************************/
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(validCrop == true)
    {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
}

/******************************************************************************
Author: John M. Weiss, Ph.D., edited by Kelsey Bellew
Description: Checks for a valid crop state, then uses the existing rubber
    band and mouse coordinates to crop the image on the screen. It then
    deletes the rubber band and tells the program that it is no longer in
    a crop state.
Paramaters: event - the current mouse event
 *****************************************************************************/
void MainWindow::mouseReleaseEvent( QMouseEvent *event )
{
    if(validCrop == true)
    {
        rubberBand->hide();

        qDebug() << "mouse release " << event->button() << " at " << "(" << event->x() << "," << event->y() << ")";

        //set the image to the cropped version of itself, and set the imageLabel to the current image
        image = image.copy(QRect(origin, event->pos()).normalized());
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->setGeometry(QRect(origin, event->pos()).normalized());
        pictureChanged = true;
        saveAct->setEnabled(true);
        saveAsAct->setEnabled(true);

        pictureChanged = true;

        delete rubberBand;
        validCrop = false;
    }
}

/******************************************************************************
Author: Caitlin Taggart
Description: Allows to enable or disable image actions. (rotate, resize, crop,
    and balance)
 *****************************************************************************/
void MainWindow::enableImageEdits(bool enable)
{
   rotateAct->setEnabled(enable);
   resizeAct->setEnabled(enable);

   cropAct->setEnabled(enable);
   balanceAct->setEnabled(enable);
}

/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Updates the enables of move forward, move backward, next photo
    and previous photo. It does this by checking where in the album we are
    and how many photos there are in the album.
 *****************************************************************************/
void MainWindow::updateMoveEnables()
{
    if (album.size() == 0)//if there are no photos disable them all
    {
        moveForwardAct->setEnabled(false);
        nextPhotoAct->setEnabled(false);
        previousPhotoAct->setEnabled(false);
        moveBackwardAct->setEnabled(false);
        return;
    }

    if (currentPicture + 1 == album.size())//should only move backward
    {
        moveForwardAct->setEnabled(false);
        nextPhotoAct->setEnabled(false);
        if (album.size() == 1) //unless of course the album size is one
        {
            previousPhotoAct->setEnabled(false);
            moveBackwardAct->setEnabled(false);
        }
        else
        {
            previousPhotoAct->setEnabled(true);
            moveBackwardAct->setEnabled(true);
        }
        return;
    }

    if (currentPicture == 0)//should only move forward
    {
        moveBackwardAct->setEnabled(false);
        previousPhotoAct->setEnabled(false);
        if (album.size() == 1)//unless of course the album size is one
        {
            nextPhotoAct->setEnabled(false);
            moveForwardAct->setEnabled(false);
        }
        else
        {
            nextPhotoAct->setEnabled(true);
            moveForwardAct->setEnabled(true);
        }
        return;
    }

    //if neither of these are the case, then enable them all.
    moveBackwardAct->setEnabled(true);
    previousPhotoAct->setEnabled(true);
    nextPhotoAct->setEnabled(true);
    moveForwardAct->setEnabled(true);
}

/******************************************************************************
Author: Caitlin Taggart and Kelsey Bellew
Description: Sets the description of the label based on how many photos are
    in the album.
 *****************************************************************************/
void MainWindow::setDescription()
{
    //set it to be empty, because there is no photo
    if (album.size() == 0)
    {
        descriptionLabel->setText("Description:\nLocation:\nDate:");
    }
    else
    {
        //get the current photo and use the information from it
        //to se the description label.
        Photo photo = album[currentPicture];
        QString str = "Description: " + photo.Description + "\n";
        str += "Locaiton: " + photo.Location + "\n";
        str += "Date: " + photo.Date.toString("MMMM d, yyyy");
        descriptionLabel->setText(str);
    }
}

/******************************************************************************
Author: Kelsey Bellew
Description: The descructor for the main window class.
 *****************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}
