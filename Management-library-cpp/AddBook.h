#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {
class AddBook;
}

class AddBook : public QDialog
{
    Q_OBJECT

public:
    explicit AddBook(QWidget *parent = nullptr);
    ~AddBook();

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::AddBook *ui;
};

#endif // ADDBOOK_H
