#ifndef SHOWALLMEMBER_H
#define SHOWALLMEMBER_H

#include <QDialog>

namespace Ui {
class ShowAllMember;
}

class ShowAllMember : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllMember(QWidget *parent = nullptr);
    ~ShowAllMember();
    void showMember();

private slots:
    void on_back_clicked();

    void on_delete_2_clicked();

    void on_edit_clicked();

private:
    Ui::ShowAllMember *ui;
};

#endif // SHOWALLMEMBER_H
