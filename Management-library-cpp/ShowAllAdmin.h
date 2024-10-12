#ifndef SHOWALLADMIN_H
#define SHOWALLADMIN_H

#include <QDialog>

namespace Ui {
class ShowAllAdmin;
}

class ShowAllAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllAdmin(QWidget *parent = nullptr);
    ~ShowAllAdmin();
    void showAdmin();
private slots:

    void on_back_clicked();

    void on_delete_2_clicked();

    void on_edit_clicked();

private:
    Ui::ShowAllAdmin *ui;
};

#endif // SHOWALLADMIN_H
