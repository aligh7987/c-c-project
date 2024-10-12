#ifndef EDITADMIN_H
#define EDITADMIN_H

#include <QDialog>

namespace Ui {
class EditAdmin;
}

class EditAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit EditAdmin(QString id,QString name,QString mobilePhone,QWidget *parent = nullptr);
    ~EditAdmin();

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::EditAdmin *ui;
    QString id;
};

#endif // EDITADMIN_H
