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

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QPlainTextEdit;
class QPixmap;
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

private slots:
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void brighten();
    void contrast();
    void edge();
    void gamma();
    void negate();
    void rotate();
    void sharpen();
    void smooth();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QImage image;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *openAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *brightenAct;
    QAction *contrastAct;
    QAction *edgeAct;
    QAction *gammaAct;
    QAction *negateAct;
    QAction *rotateAct;
    QAction *sharpenAct;
    QAction *smoothAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *viewToolBar;
};

#endif // MAINWINDOW_H
