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

private slots: //was public and it was fine, but.
    void brighten(int);
    void contrast();
    void edge();
    void gamma();
    void negate();
    void sharpen();
    void smooth();

private:
    Ui::pictureedits *ui;

    void createActions();

    QLabel *picImageLabel;
    QImage *picImage;

    int brightenPrevVal;

};

#endif // PICTUREEDITS_H
