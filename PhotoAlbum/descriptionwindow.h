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
    QString* description;
    QString* location;
    QDate* date;
    void show();
    explicit DescriptionWindow();
    ~DescriptionWindow();

private slots:
    void on_buttonBox_accepted();

signals:
    void descriptionChanged();

private:
    Ui::DescriptionWindow *ui;
};

#endif // DESCRIPTIONWINDOW_H
