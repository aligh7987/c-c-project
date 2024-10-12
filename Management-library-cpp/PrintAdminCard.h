#ifndef PRINTADMINCARD_H
#define PRINTADMINCARD_H

#include <QDialog>

namespace Ui {
class PrintAdminCard;
}

class PrintAdminCard : public QDialog
{
    Q_OBJECT

public:
    explicit PrintAdminCard(QWidget *parent = nullptr);
    ~PrintAdminCard();

private slots:
    void on_showCard_clicked();

    void on_back_clicked();

    void on_print_2_clicked();

private:
    Ui::PrintAdminCard *ui;
};

#endif // PRINTADMINCARD_H
