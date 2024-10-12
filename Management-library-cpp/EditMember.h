#ifndef EDITMEMBER_H
#define EDITMEMBER_H

#include <QDialog>

namespace Ui {
class EditMember;
}

class EditMember : public QDialog
{
    Q_OBJECT

public:

    explicit EditMember(QString mmbrshipNum,QString name,QString father,QString ncode,QString birthday,QString mobile,QString email,QWidget *parent = nullptr);
    ~EditMember();

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::EditMember *ui;
    QString id;
};

#endif // EDITMEMBER_H
