#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>

namespace Ui {
class EditBook;
}

class EditBook : public QDialog
{
    Q_OBJECT

public:
    //id,name,writer,publisher,translater,year,genre,range,this
    explicit EditBook(QString id,QString name,QString writer,QString publisher,QString translater,QString year,QString genre,QString range,QWidget *parent = nullptr);
    ~EditBook();

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::EditBook *ui;
    QString id;
};

#endif // EDITBOOK_H
