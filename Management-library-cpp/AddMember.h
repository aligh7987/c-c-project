#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QDialog>

namespace Ui {
class AddMember;
}

class AddMember : public QDialog
{
    Q_OBJECT

public:
    explicit AddMember(QWidget *parent = nullptr);
    ~AddMember();

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::AddMember *ui;
};

#endif // ADDMEMBER_H
