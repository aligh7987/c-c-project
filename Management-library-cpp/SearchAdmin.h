#ifndef SEARCHADMIN_H
#define SEARCHADMIN_H

#include <QDialog>

namespace Ui {
class SearchAdmin;
}

class SearchAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit SearchAdmin(QWidget *parent = nullptr);
    void showAdmin();
    ~SearchAdmin();

private slots:
    void on_search_clicked();

    void on_back_clicked();

    void on_edit_clicked();

    void on_delete_2_clicked();

private:
    Ui::SearchAdmin *ui;
};

#endif // SEARCHADMIN_H
