#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H
#include "Login.h"
#include <QDialog>
using namespace std;
namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPassword(QWidget *parent = nullptr);
    ~ForgetPassword();
void reject();
void generateErr(ifstream& f);
private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::ForgetPassword *ui;

};

#endif // FORGETPASSWORD_H
