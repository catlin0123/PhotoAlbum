#ifndef PICTUREEDITS_H
#define PICTUREEDITS_H

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
#include <math.h> //??

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QPixmap;
QT_END_NAMESPACE

namespace Ui {
class pictureedits;
}

class pictureedits : public QWidget
{
    Q_OBJECT

public:
    explicit pictureedits(QImage *image, QLabel *imageLabel);
    ~pictureedits();

public slots:
    void brighten(int);
    void contrast(int);
    void edge();
    void gamma(int);
    void negate();
    void rotate();
    void sharpen(int);
    void smooth(int);

private:
    Ui::pictureedits *ui;

    void createActions();

    QAction *brightenAct;
    QAction *contrastAct;
    QAction *edgeAct;
    QAction *gammaAct;
    QAction *negateAct;
    QAction *rotateAct;
    QAction *sharpenAct;
    QAction *smoothAct;

    QLabel *picImageLabel;
    QImage *picImage;
};

#endif // PICTUREEDITS_H
