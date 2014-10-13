#ifndef DESCRIPTIONWINDOW_H
#define DESCRIPTIONWINDOW_H

#include <QDialog>

namespace Ui {
class DescriptionWindow;
}

class DescriptionWindow : public QDialog
{
    Q_OBJECT

public:
//    explicit DescriptionWindow(QWidget *parent = 0);

    explicit DescriptionWindow(QString *description, QString *title);
    ~DescriptionWindow();

public slots:
    void setImageDescription();

private:
    Ui::DescriptionWindow *ui;

    QString *localDescription;
    QString *localTitle;
};

#endif // DESCRIPTIONWINDOW_H
