#ifndef SHOWALLBOOKS_H
#define SHOWALLBOOKS_H

#include <QDialog>

namespace Ui {
class ShowAllBooks;
}

class ShowAllBooks : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllBooks(QWidget *parent = nullptr);
    ~ShowAllBooks();
    void showBooks();
private slots:
    void on_back_clicked();

    void on_delete_2_clicked();

    void on_edit_clicked();

private:
    Ui::ShowAllBooks *ui;
};

#endif // SHOWALLBOOKS_H
