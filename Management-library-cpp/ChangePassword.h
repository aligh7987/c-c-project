#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QString userName,QWidget *parent = nullptr);
    ~ChangePassword();
private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::ChangePassword *ui;
    QString username;
};

#endif // CHANGEPASSWORD_H
