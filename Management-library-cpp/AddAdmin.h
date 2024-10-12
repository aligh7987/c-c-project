#ifndef ADDADMIN_H
#define ADDADMIN_H

#include <QDialog>

namespace Ui {
class AddAdmin;
}

class AddAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit AddAdmin(QWidget *parent = nullptr);
    ~AddAdmin();

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::AddAdmin *ui;
};

#endif // ADDADMIN_H
