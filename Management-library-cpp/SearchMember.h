#ifndef SEARCHMEMBER_H
#define SEARCHMEMBER_H

#include <QDialog>

namespace Ui {
class SearchMember;
}

class SearchMember : public QDialog
{
    Q_OBJECT

public:
    explicit SearchMember(QWidget *parent = nullptr);
    ~SearchMember();
    void showMember();
private slots:
    void on_search_clicked();

    void on_back_clicked();

    void on_edit_clicked();

    void on_delete_2_clicked();

private:
    Ui::SearchMember *ui;
};

#endif // SEARCHMEMBER_H
