/******************************************************************************
File: This file contains the header information for the MainWindow class.
 *****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtGui>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QtDebug>
#include <QRubberBand>
#include <QMatrix>
#include "pictureedits.h"
#include "resizewindow.h"
#include "xmlparser.h"
#include "descriptionwindow.h"
#include "Photo.h"
#include <QLayout>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QPlainTextEdit;
class QPixmap;
class QRubberBand;
class QMatrix;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //is this the right place?
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
//    void keyPressEvent( QKeyEvent *event );

private slots:
    void newAlbum();
    void open();
    void save();
    void saveAs();
    void close();
    void updateDescription();
    void addPhoto();
    void deletePhoto();
    void editDescription();
    void nextPhoto();
    void previousPhoto();
    void moveForward();
    void moveBackward();

//    void zoomIn();
//    void zoomOut();
//    void normalSize();
//    void fitToWindow();

    void about();
    void balance();
    void rotate();
    void openResize();
    void crop();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void updateActions();
    void enableImageEdits(bool enable);
    void updateMoveEnables();
    void setDescription();
//    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    //widgets that make up the main window
    QLabel *imageLabel;
    QImage image;
    QScrollArea *scrollArea;
    QLabel *descriptionLabel;
    QVBoxLayout *layout;
    QWidget *widget;
    double scaleFactor;

    //actions
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QAction *addPhotoAct;
    QAction *deletePhotoAct;
    QAction *editDescriptionAct;
    QAction *nextPhotoAct;
    QAction *previousPhotoAct;
    QAction *moveForwardAct;
    QAction *moveBackwardAct;

//    QAction *zoomInAct;
//    QAction *zoomOutAct;
//    QAction *normalSizeAct;
//    QAction *fitToWindowAct;

    QAction *aboutAct;
    QAction *balanceAct;
    QAction *rotateAct;
    QAction *resizeAct;
    QAction *cropAct;

    //menus
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *imageMenu;

    //toolbars
    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    //dialog boxes
    pictureedits *balanceWidget;
    ResizeWindow *resizeDialog;
    DescriptionWindow *descriptionDialog;

    //used for cropping
    QRubberBand *rubberBand;
    QPoint origin;
    bool validCrop;

    //used for file management
    //and album management
    bool pictureChanged;
    bool albumChanged;
    bool newFile;
    int currentPicture;
    QString filename;
    vector<Photo> album;
};

#endif // MAINWINDOW_H
