#ifndef DELETEBOOK_H
#define DELETEBOOK_H

#include <QDialog>

namespace Ui {
class DeleteBook;
}

class DeleteBook : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteBook(QWidget *parent = nullptr);
    ~DeleteBook();

private slots:
    void on_back_clicked();

    void on_delete_2_clicked();

private:
    Ui::DeleteBook *ui;
};

#endif // DELETEBOOK_H
