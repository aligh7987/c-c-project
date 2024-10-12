#ifndef LENDINGBOOK_H
#define LENDINGBOOK_H

#include <QDialog>

namespace Ui {
class LendingBook;
}

class LendingBook : public QDialog
{
    Q_OBJECT

public:
    explicit LendingBook(QWidget *parent = nullptr);
    ~LendingBook();

private slots:
    void on_search_clicked();

    void on_lendBook_clicked();

    void on_back_clicked();

private:
    Ui::LendingBook *ui;
    int countOfBook;
    QList<QString> m;
};

#endif // LENDINGBOOK_H
