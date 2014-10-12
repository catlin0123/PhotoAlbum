#ifndef DESCRIPTIONWINDOW_H
#define DESCRIPTIONWINDOW_H

#include <QWidget>

namespace Ui {
class DescriptionWindow;
}

class DescriptionWindow : public QWidget
{
    Q_OBJECT

public:
//    explicit DescriptionWindow(QWidget *parent = 0);
    explicit DescriptionWindow(QString *description, QString *title);
    ~DescriptionWindow();

private slots:
    void setImageDescription();
    void cancelClicked();

private:
    Ui::DescriptionWindow *ui;

    QString *localDescription;
       QString *localTitle;
};

#endif // DESCRIPTIONWINDOW_H
