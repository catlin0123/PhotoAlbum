#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    validCrop = false;
    pictureChanged = false;
    albumChanged = false;
    newFile = true;
    currentPicture = 0;

    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    descriptionLabel = new QLabel;
    descriptionLabel->setMinimumHeight(40);
    descriptionLabel->setText("Description:\nLocation:\nDate:");

    widget = new QWidget;
    layout = new QVBoxLayout(widget);
    layout->addWidget(scrollArea);
    layout->addWidget(descriptionLabel);
    setCentralWidget(widget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    this->balanceWidget = new pictureedits(&image, imageLabel);
    this->resizeDialog = new ResizeWindow(&image, imageLabel);
    this->descriptionDialog = new DescriptionWindow();
    connect(descriptionDialog, SIGNAL(descriptionChanged()), this, SLOT(updateDescription()));

    setWindowTitle(tr("Photo Album"));
    resize(800, 600);

    this->ui->mainToolBar->hide();
}

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
    album = vector<Photo>();
    image = QImage();
    newFile = true;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.width(), image.height());
    setDescription();
    enableImageEdits(false);
    deletePhotoAct->setEnabled(false);
    updateMoveEnables();
    saveAct->setEnabled(false);
    saveAsAct->setEnabled(false);
}

void MainWindow::open()
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

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("XML files (*.xml)"));
    if (!fileName.isEmpty())
    {
        filename = fileName;
        newFile = false;
        QFile* file = new QFile(filename);
        Parser parse;
        currentPicture = 0;
        album = parse.GetPhotoAlbums(file);
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
    updateMoveEnables();
    setDescription();
    saveAct->setEnabled(false);
    saveAsAct->setEnabled(false);
}

void MainWindow::save()
{
    if (newFile)
    {
        saveAs();
    }
    else
    {
        if (pictureChanged)
        {
            image.save(album[currentPicture].FileName);
        }
        QFile file;
        newFile = false;
        file.setFileName(filename);
        file.open(QIODevice::ReadWrite);
        Parser parse;
        QString string = parse.ConvertList(album);
        QTextStream stream(&file);
        stream << string;
        file.close();
        albumChanged = false;
    }
}

void MainWindow::saveAs()
{
    if (pictureChanged)
    {
        image.save(album[currentPicture].FileName);
    }
    //save the album and close the program
    QFile file;
    filename = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("XML files (*.xml)"));
    newFile = false;
    file.setFileName(filename);
    file.open(QIODevice::ReadWrite);
    Parser parse;
    QString string = parse.ConvertList(album);
    QTextStream stream(&file);
    stream << string;
    file.close();
    albumChanged = false;
}

void MainWindow::close()
{
    if (albumChanged)
    {
        int response = QMessageBox::information(this, tr("Save"),
                tr("Save changes before closing?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);

        switch (response)
        {
            case QMessageBox::Save :
            {
                if (pictureChanged)
                {
                    image.save(album[currentPicture].FileName);
                }
                //save the album and close the program
                QFile file;
                if (newFile)
                {
                    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("XML files (*.xml)"));
                    file.setFileName(fileName);
                    file.open(QIODevice::ReadWrite);
                }
                else
                {
                    file.setFileName(filename);
                    file.open(QIODevice::ReadWrite);
                }

                //get the string to output
                Parser parse;
                QString string = parse.ConvertList(album);
                QTextStream stream(&file);
                stream << string;
                file.close();

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
        QApplication::quit();
    }
}

void MainWindow::addPhoto()
{
    Photo photo;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName != "")
    {
        image = QImage(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.width(), image.height());
        enableImageEdits(true);
        photo.FileName = fileName;
        album.push_back(photo);
        currentPicture = album.size() - 1;
        albumChanged = true;
        setDescription();
    }
    if (album.size() != 0)
    {
        deletePhotoAct->setEnabled(true);
        editDescriptionAct->setEnabled(true);
    }
    updateMoveEnables();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

void MainWindow::deletePhoto()
{
    if (album.size() != 0)
    {
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
                    image = QImage(album[currentPicture].FileName);
                    imageLabel->setPixmap(QPixmap::fromImage(image));
                    imageLabel->resize(image.width(), image.height());
                }
                else
                {
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
        deletePhotoAct->setEnabled(false);
        editDescriptionAct->setEnabled(false);
    }
    updateMoveEnables();
    setDescription();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

void MainWindow::editDescription()
{
    descriptionDialog->location = &album[currentPicture].Location;
    descriptionDialog->description = &album[currentPicture].Description;
    descriptionDialog->date = &album[currentPicture].Date;
    descriptionDialog->show();
}

void MainWindow::updateDescription()
{
    album[currentPicture].Description = *(descriptionDialog->description);
    album[currentPicture].Location = *(descriptionDialog->location);
    album[currentPicture].Date = *(descriptionDialog->date);
    albumChanged = true;
    setDescription();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

void MainWindow::nextPhoto()
{
    if (currentPicture != album.size() - 1 && album.size() != 0)
    {
        if (pictureChanged)
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
        currentPicture = currentPicture + 1;
        image = QImage(album[currentPicture].FileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.width(), image.height());
        pictureChanged = false;
    }
    updateMoveEnables();
    setDescription();
}

void MainWindow::previousPhoto()
{
    if (currentPicture != 0)
    {
        if (pictureChanged)
        {
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
        currentPicture = currentPicture - 1;
        image = QImage(album[currentPicture].FileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.width(), image.height());
        pictureChanged = false;
    }
    updateMoveEnables();
    setDescription();
}

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
    updateMoveEnables();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

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
    updateMoveEnables();
    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);
}

void MainWindow::about()
{
    QString str;
    str = "Photo Album allows you to add, delete, edit, and add a description to photos.";
    QMessageBox::about(this, tr("About Photo Album"), str);
}

void MainWindow::balance()
{
    //show balance window
    this->balanceWidget->show();

    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);

    pictureChanged = true;
}

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
    //also rotate, resize, crop.

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(imageMenu);
    menuBar()->addMenu(helpMenu);
}

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

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::updateActions()
{
    rotateAct->setEnabled(true);
    resizeAct->setEnabled(true);
    cropAct->setEnabled(true);
    balanceAct->setEnabled(true);
}


void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::rotate()
{
    if(image.isNull())
    {
        qDebug() << "image does not exist- you should do a check for this, srsly";// << fileName;
        exit(-2);
    }

//    QPixmap pix(*imageLabel->pixmap());

//    //create a Qtransform for rotation (can also use for translation and scaling)
//    QTransform *t = new QTransform;

//    //rotate pixmap by 45 degrees
//    QPixmap rpix(pix.transformed(t->rotate(45)));
////                image.transformed(t->rotate(45)));

//    //scale to original image dimensions, retaining aspect ratio
//    QPixmap spix(rpix.scaled(image.width(), image.height(), Qt::KeepAspectRatio));

//    //store in label's pixmap
//    imageLabel->setPixmap(spix);

//    //more concisely, can collapse the previous three lines into one:
//    imageLabel->setPixmap(pix.transformed(t->rotate( 45 )).scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));

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
    imageLabel->setPixmap(pix.scaled(h, w, Qt::KeepAspectRatio)); //will this continue to be a thing when we have changes something?
    imageLabel->setFixedSize(h, w);

    pictureChanged = true;
}

void MainWindow::openResize()
{
    //show resize window
    resizeDialog->show();

    saveAct->setEnabled(true);
    saveAsAct->setEnabled(true);

    pictureChanged = true;
}

void MainWindow::crop()
{
    //get a new instance of a rubberband and tell the program that we are cropping
    rubberBand = new QRubberBand( QRubberBand::Rectangle, this );
    validCrop = true;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //set the origin and set up the rubberband, if rubberband exists
    if(validCrop == true)
    {
        origin = event->pos();

        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
    }
    //qDebug() << "mouse press   " << event->button() << " at " << "(" << event->x() << "," << event->y() << ")";
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(validCrop == true)
    {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
}

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

void MainWindow::enableImageEdits(bool enable)
{
   rotateAct->setEnabled(enable);
   resizeAct->setEnabled(enable);

   cropAct->setEnabled(enable);
   balanceAct->setEnabled(enable);
}

void MainWindow::updateMoveEnables()
{
    if (album.size() == 0)
    {
        moveForwardAct->setEnabled(false);
        nextPhotoAct->setEnabled(false);
        previousPhotoAct->setEnabled(false);
        moveBackwardAct->setEnabled(false);
        return;
    }

    if (currentPicture + 1 == album.size())
    {
        moveForwardAct->setEnabled(false);
        nextPhotoAct->setEnabled(false);
        if (album.size() == 1)
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

    if (currentPicture == 0)
    {
        moveBackwardAct->setEnabled(false);
        previousPhotoAct->setEnabled(false);
        if (album.size() == 1)
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
    moveBackwardAct->setEnabled(true);
    previousPhotoAct->setEnabled(true);
    nextPhotoAct->setEnabled(true);
    moveForwardAct->setEnabled(true);
}

void MainWindow::setDescription()
{
    if (album.size() == 0)
    {
        descriptionLabel->setText("Description:\nLocation:\nDate:");
    }
    else
    {
        Photo photo = album[currentPicture];
        QString str = "Description: " + photo.Description + "\n";
        str += "Locaiton: " + photo.Location + "\n";
        str += "Date: " + photo.Date.toString("MMMM d, yyyy");
        descriptionLabel->setText(str);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
