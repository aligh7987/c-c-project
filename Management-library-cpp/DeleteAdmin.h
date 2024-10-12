#ifndef DELETEADMIN_H
#define DELETEADMIN_H

#include <QDialog>

namespace Ui {
class DeleteAdmin;
}

class DeleteAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteAdmin(QWidget *parent = nullptr);
    ~DeleteAdmin();

private slots:
    void on_back_clicked();

    void on_delete_2_clicked();

private:
    Ui::DeleteAdmin *ui;
};

#endif // DELETEADMIN_H
