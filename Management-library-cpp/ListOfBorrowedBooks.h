#ifndef LISTOFBORROWEDBOOKS_H
#define LISTOFBORROWEDBOOKS_H
#include "Member.h"
#include <QDialog>

namespace Ui {
class ListOfBorrowedBooks;
}

class ListOfBorrowedBooks : public QDialog
{
    Q_OBJECT

public:
    explicit ListOfBorrowedBooks(Member* m=nullptr,QWidget *parent = nullptr);
    ~ListOfBorrowedBooks();

private slots:
    void on_back_clicked();

private:
    Ui::ListOfBorrowedBooks *ui;
    Member* tmp;
};

#endif // LISTOFBORROWEDBOOKS_H
