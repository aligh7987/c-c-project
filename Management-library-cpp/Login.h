#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include "User.h"
#include "Admin.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    void reject();
    ~Login();

private slots:
    void on_login_clicked();

    void on_forgotPas_clicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
