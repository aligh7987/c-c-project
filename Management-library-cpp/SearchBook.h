#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H

#include <QDialog>

namespace Ui {
class SearchBook;
}

class SearchBook : public QDialog
{
    Q_OBJECT

public:
    explicit SearchBook(QWidget *parent = nullptr);
    ~SearchBook();
    void showBooks();
private slots:
    void on_back_clicked();

    void on_delete_2_clicked();

    void on_edit_clicked();

    void on_search_clicked();

private:
    Ui::SearchBook *ui;
};

#endif // SEARCHBOOK_H
