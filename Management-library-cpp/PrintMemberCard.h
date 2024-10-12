#ifndef PRINTMEMBERCARD_H
#define PRINTMEMBERCARD_H

#include <QDialog>

namespace Ui {
class PrintMemberCard;
}

class PrintMemberCard : public QDialog
{
    Q_OBJECT

public:
    explicit PrintMemberCard(QWidget *parent = nullptr);
    ~PrintMemberCard();

private slots:
    void on_showCard_clicked();

    void on_back_clicked();

    void on_print_clicked();

private:
    Ui::PrintMemberCard *ui;
};

#endif // PRINTMEMBERCARD_H
