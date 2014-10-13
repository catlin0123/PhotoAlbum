#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QtDebug>
#include <QRubberBand>
#include "pictureedits.h"
#include "resizewindow.h"
#include "xmlparser.h"
#include "descriptionwindow.h"
#include "Photo.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QPlainTextEdit;
class QPixmap;
class QRubberBand;
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
//    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QImage image;
    QScrollArea *scrollArea;
    double scaleFactor;

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

    QMenu *fileMenu;
    QMenu *editMenu;
//    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *imageMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
//    QToolBar *viewToolBar;

    pictureedits *balanceWidget;
    ResizeWindow *resizeDialog;
    DescriptionWindow *descriptionDialog;

    QRubberBand *rubberBand;
    QPoint origin;

    bool validCrop;
    bool pictureChanged;
    bool albumChanged;
    bool newFile;
    int currentPicture;
    QString filename;
    vector<Photo> album;
};

#endif // MAINWINDOW_H
